#include "edl/edl.h"
#include "mathutil.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <vector>
#include <iostream>


EDL::EDL(int sobelKernelSize, double sobelScale, double sobelDelta, int gaussianKernelSize,
         int anchorThreshold, double angleTolerance, unsigned int minLineLength)
    : sobelKernelSize(sobelKernelSize),
      sobelScale(sobelScale),
      sobelDelta(sobelDelta),
      gaussianKernelSize(gaussianKernelSize),
      anchorThreshold(anchorThreshold),
      angleTolerance(angleTolerance),
      minLineLength(minLineLength)
{
}

EDL::~EDL()
{
}

std::vector<Line> EDL::calculate(cv::InputArray _image)
{
    cv::Mat image = _image.getMat();
    std::vector<Line> result;

    if(!image.data)
        return result;

    //Definitions for sobel
    cv::Mat dx;
    cv::Mat dy;
    cv::Mat adx;
    cv::Mat ady;

    //Definitions for grad, angle and anchor calculation
    cv::Mat gradientMagnitudes = cv::Mat::zeros(image.rows, image.cols, CV_8U);
    cv::Mat gradientAngles = cv::Mat::zeros(image.rows, image.cols, CV_64F);
    std::vector<cv::Point> anchors;

    // ####
    // use a filter algorithm to suppress noise
    // ####
    cv::GaussianBlur(image, image, cv::Size(gaussianKernelSize, gaussianKernelSize), 0, 0);


    // ####
    // run the edge operator
    // ####

    cv::Sobel(image, dx, CV_16S, 1, 0, sobelKernelSize, sobelScale, sobelDelta, cv::BORDER_DEFAULT);
    cv::Sobel(image, dy, CV_16S, 0, 1, sobelKernelSize, sobelScale, sobelDelta, cv::BORDER_DEFAULT);
    convertScaleAbs( dx, adx ); //decrease to CV_8U again
    convertScaleAbs( dy, ady ); //always use adx, ady to proceed!

    // ####
    // create gradient and direction output including the anchorpoints
    // ####

    calcGradAngleAnchors(adx, ady, gradientMagnitudes, gradientAngles, anchors);

    // ####
    // run the routing algorithm
    // ####
    routeAnchors(angleTolerance, gradientMagnitudes, gradientAngles, anchors, result);

    // Save result
    return result;
}

bool EDL::isAnchor(cv::Mat& src, int row, int column)
{
    bool isanchor = false;

    // prevent border pixles from being anchors.
    if (row > 0 && column > 0 && row < src.rows && column < src.cols)
    {
        int center = src.at<uchar>(row, column);
        int top = src.at<uchar>(row, column + 1);
        int bottom = src.at<uchar>(row, column - 1);
        int right = src.at<uchar>(row + 1, column);
        int left = src.at<uchar>(row - 1, column);

        if (center - top >= anchorThreshold && center - bottom >= anchorThreshold)
            isanchor = true;

        if (center - right >= anchorThreshold && center - left >= anchorThreshold)
            isanchor = true;
    }
    return isanchor;
}

void EDL::calcGradAngleAnchors(cv::InputArray _gradientX, cv::InputArray _gradientY, cv::OutputArray _gradientMagnitudes, cv::OutputArray _gradientAngles, std::vector<cv::Point> &anchors)
{
    cv::Mat gradientX = _gradientX.getMat();
    cv::Mat gradientY = _gradientY.getMat();
    cv::Mat gradientAngles = _gradientAngles.getMat();
    cv::Mat gradientMagnitudes = _gradientMagnitudes.getMat();
    int nRows = gradientMagnitudes.rows;
    int nCols = gradientMagnitudes.cols;

    for(int row = 0; row < nRows; ++row)
    {
        const uchar* xRow = gradientX.ptr<uchar>(row);
        const uchar* yRow = gradientY.ptr<uchar>(row);
        uchar* magnitudesRow = gradientMagnitudes.ptr<uchar>(row);
        double* anglesRow = gradientAngles.ptr<double>(row);

        for(int column = 0; column < nCols; ++column)
        {
            double x0 = xRow[column];
            double y0 = yRow[column];
            magnitudesRow[column] = math::sqrtFast(x0*x0 + y0*y0);

            anglesRow[column] = std::atan2(y0, x0);

            if(isAnchor(gradientMagnitudes, row, column))
                anchors.push_back(cv::Point(column,row));
        }
    }
}

void EDL::routeAnchors(double angleTolerance, cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point>& anchorPoints, std::vector<Line> &result)
{
    CV_Assert(magnitudes.type() == CV_8U);
    CV_Assert(angles.type() == CV_64F);

    cv::Mat_<uchar> gradientMagnitudes = magnitudes.getMat();
    cv::Mat_<double> gradientAngles = angles.getMat();
    cv::Mat_<uchar> edgels = cv::Mat::zeros(gradientMagnitudes.rows, gradientMagnitudes.cols, CV_8U);
    std::vector<std::list<cv::Point*>*> lineSegments;

    // Iterate all anchor points
    for(auto anchorPoint : anchorPoints)
    {
        // Is the pixel already part of an edge?
        if(edgels(anchorPoint) != 0)
        {
            continue;
        }

        walkFromAnchor(anchorPoint, angleTolerance, gradientMagnitudes, gradientAngles, edgels, lineSegments);
    }

    // Create result
    for(auto lineSegment : lineSegments)
    {
        if(lineSegment->size() >= minLineLength)
        {
            cv::Point* start = lineSegment->front();
            cv::Point* end = lineSegment->back();

            result.push_back(Line(*start, *end));
        }
    }

    // Free lineSegments
    for(auto lineSegment : lineSegments)
    {
        for(auto point : *lineSegment)
        {
            delete point;
        }
        delete lineSegment;
    }
}

void EDL::walkFromAnchor(cv::Point& anchorPoint, double angleTolerance, cv::Mat_<uchar>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<uchar> &edgels, std::vector<std::list<cv::Point*>*>& lineSegments)
{
    // Used to recalculate currentGradeintAngle
    double currentGradientAngle = gradientAngles(anchorPoint);
    double sx = cos(currentGradientAngle);
    double sy = sin(currentGradientAngle);
    double lineSegmentAngle = currentGradientAngle;

    cv::Point* point = new cv::Point(anchorPoint);

    std::list<cv::Point*>* currentLineSegment = new std::list<cv::Point*>;
    lineSegments.push_back(currentLineSegment);

    int mainDirection = getDirection(gradientAngles(anchorPoint));
    int subDirection = -1;
    bool stopWalk = false;

    do
    {
        // Break if pixle returned by findNextPoint() would be out of range.
        // TODO: Find better solution?
        if( point->x+1 >= gradientAngles.cols || point->y+1 >= gradientAngles.rows || point->x < 1 || point->y < 1 )
        {
            stopWalk = true;
            continue;
        }

        // ####
        // Check if a new segment begins
        // ####
        currentGradientAngle = gradientAngles(*point);

        // currentGradientAngle is not in lineSegmentAngle's tolerance
        if(!isAligned(lineSegmentAngle, currentGradientAngle, angleTolerance))
        {
            currentLineSegment = new std::list<cv::Point*>;
            lineSegments.push_back(currentLineSegment);
            // Reset line segment angle computation
            sx = 0;
            sy = 0;
        }

        if(subDirection == -1)
            currentLineSegment->push_front(point);
        else
            currentLineSegment->push_back(point);

        edgels(*point) = 255;

        // ####
        // Recalculate the segment angle
        // ####
        sx += cos(currentGradientAngle);
        sy += sin(currentGradientAngle);
        lineSegmentAngle = std::atan2(sy, sx);

        // ####
        // Find next point
        // ####
        point = findNextPoint(point, mainDirection, subDirection, gradientMagnitudes);

        // ####
        // Check if end reached, change direction if necessary or quit loop
        // ####
        if(isOutOfBounds(point, gradientMagnitudes)
           || gradientMagnitudes(*point) <= 0
           || getDirection(gradientAngles(*point)) != mainDirection
           || edgels(*point)  != 0)
        {
            // Change direction
            if(subDirection == -1)
            {
                delete point;
                subDirection = 1;

                point = findNextPoint(&anchorPoint, mainDirection, subDirection, gradientMagnitudes);

                currentLineSegment = lineSegments.at(0);
                // TODO: This should be set to the angle of the first lnie segment, not just to the
                // angle of the anchorPoint!
                lineSegmentAngle = gradientAngles(anchorPoint);
                sx = cos(currentGradientAngle);
                sy = sin(currentGradientAngle);

                if(isOutOfBounds(point, gradientMagnitudes))
                    stopWalk = true;
            }
            // Already examined both directions so let's quit
            else
            {
                delete point;
                stopWalk = true;
                continue;
            }
        }
    } while(!stopWalk);
}

bool EDL::getDirection(double angle)
{
    if( fabs(cos(angle)) >= fabs(sin(angle)) )
    {
        return VERTICAL;
    }
    return HORIZONTAL;
}

cv::Point* EDL::findNextPoint(cv::Point* currentPoint, int mainDirection, int subDirection, cv::Mat_<uchar>& gradientMagnitudes)
{
    if(mainDirection == HORIZONTAL)
    {
        if(   gradientMagnitudes(currentPoint->y + 1, currentPoint->x + subDirection) > gradientMagnitudes(currentPoint->y,     currentPoint->x + subDirection)
           && gradientMagnitudes(currentPoint->y + 1, currentPoint->x + subDirection) > gradientMagnitudes(currentPoint->y - 1, currentPoint->x + subDirection))
        {
            return new cv::Point(currentPoint->x + subDirection, currentPoint->y + 1);
        }
        else if (gradientMagnitudes(currentPoint->y, currentPoint->x + subDirection)  > gradientMagnitudes(currentPoint->y - 1, currentPoint->x + subDirection))
        {
            return new cv::Point(currentPoint->x + subDirection, currentPoint->y);
        }
        else
        {
            return new cv::Point(currentPoint->x + subDirection, currentPoint->y - 1);
        }
    }
    // VERTICAL
    else
    {
        if(   gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x + 1) > gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x)
           && gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x + 1) > gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x - 1))
        {
            return new cv::Point(currentPoint->x + 1, currentPoint->y + subDirection);
        }
        else if (gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x)  > gradientMagnitudes(currentPoint->y + subDirection, currentPoint->x - 1))
        {
            return new cv::Point(currentPoint->x, currentPoint->y + subDirection);
        }
        else
        {
            return new cv::Point(currentPoint->x - 1, currentPoint->y + subDirection);
        }
    }
}

bool EDL::isAligned(double compare, double angle, double tolerance)
{
    CV_Assert(compare <= 2 * math::m_pi && compare >= 0);
    CV_Assert(angle <= 2 * math::m_pi && angle >= 0);

    if(compare >= math::m_pi)
        compare -= math::m_pi;
    if(angle >= math::m_pi)
        angle -= math::m_pi;

    return ((angle - compare) <= tolerance) && ((angle - compare) >= -tolerance);
}

bool EDL::isOutOfBounds(cv::Point *point, cv::InputArray matrix)
{
    cv::Mat mat = matrix.getMat();

    return (point->x < 0) || (point->x > mat.cols)
            || (point->y < 0) || (point->y > mat.rows);
}
