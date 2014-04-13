#ifndef M_PI
#define M_PI 3.141592654
#endif

#include "edl/edl.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <vector>
#include <iostream>


EDL::EDL()
    : ksize(3),
      scale(1),
      delta(0),
      threshold(36),
      angleTolerance(22.5 * M_PI / 180.0d)
{
}

EDL::~EDL()
{
}

void EDL::calculate()
{
    cv::Mat src = cv::imread(getInputFilePath().c_str());

    if(!src.data)
        return;

    //Definitions for sobel
    cv::Mat dx;
    cv::Mat dy;
    cv::Mat adx;
    cv::Mat ady;

    //Definitions for grad, angle and anchor calculation
    cv::Mat gradientMagnitudes = cv::Mat::zeros(src.rows, src.cols, CV_8U);
    cv::Mat gradientAngles = cv::Mat::zeros(src.rows, src.cols, CV_32F);
    std::vector<cv::Point> anchors;

    // ####
    // use a filter algorithm to suppress noise
    // ####


    // ####
    // run the edge operator
    // ####

    cv::Sobel(src, dx, CV_16S, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);
    cv::Sobel(src, dy, CV_16S, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs( dx, adx ); //decrease to CV_8U again
    convertScaleAbs( dy, ady ); //always use adx, ady to proceed!

    // ####
    // create gradient and direction output including the anchorpoints
    // ####

    calcGradAngleAnchors(adx, ady, gradientMagnitudes, gradientAngles, anchors);

    // ####
    // run the routing algorithm
    // ####
    std::vector<Line*> result;
    routeAnchors(angleTolerance, gradientMagnitudes, gradientAngles, anchors, result);

    // Save result
    setResult(&result, 0.0d);
}

bool EDL::isAnchor(cv::Mat& src, int x, int y){
    bool isanchor = false;
    if (x > 0 && y > 0 && x < src.rows && y < src.cols) { //skip the first row of pixels
        int center = src.at<uchar>(x,y);
        int top = src.at<uchar>(x,y+1);
        int bottom = src.at<uchar>(x,y-1);
        int right = src.at<uchar>(x+1,y);
        int left = src.at<uchar>(x-1,y);
        if (center - top >= threshold && center - bottom >= threshold) {
            isanchor = true;
        }
        if (center - right >= threshold && center - left >= threshold) {
            isanchor = true;
        }
    }
    return isanchor;
}

void EDL::calcGradAngleAnchors(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle, std::vector<cv::Point> &anchors){
    cv::Mat X = gradientX.getMat();
    cv::Mat Y = gradientY.getMat();
    cv::Mat Ang = gradientAngle.getMat();
    cv::Mat Mag = gradientMagnitude.getMat();
    int nRows = Mag.rows;
    int nCols = Mag.cols;

    for(int i = 0; i < nRows; ++i){
        const uchar *x = X.ptr<uchar>(i);
        const uchar *y = Y.ptr<uchar>(i);
        uchar* p_mag = Mag.ptr<uchar>(i);
        float* p_ang = Ang.ptr<float>(i);

        for (int j = 0; j < nCols; ++j){
            float x0 = x[j], y0 = y[j];
            p_mag[j] = std::sqrt(x0*x0 + y0*y0);
            p_ang[j] = (M_PI/180) * cv::fastAtan2(y0, x0);
                if(isAnchor(Mag, i, j))
                {
                    anchors.push_back(cv::Point(i,j));
                }
        }
    }
}

void EDL::routeAnchors(double angleTolerance, cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point>& anchorPoints, std::vector<Line*>& result)
{
    CV_Assert(magnitudes.type() == CV_8U);
    CV_Assert(angles.type() == CV_64F);

    cv::Mat_<uchar> gradientMagnitudes = magnitudes.getMat();
    cv::Mat_<double> gradientAngles = angles.getMat();
    cv::Mat_<bool> edgels = cv::Mat::zeros(gradientMagnitudes.rows, gradientMagnitudes.cols, CV_8U);
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
        cv::Point* start = lineSegment->front();
        cv::Point* end = lineSegment->back();

        Line* line = new Line(*start, *end);
        result.push_back(line);
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

void EDL::walkFromAnchor(cv::Point& anchorPoint, double angleTolerance, cv::Mat_<uchar>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<bool> &edgels, std::vector<std::list<cv::Point*>*>& lineSegments)
{
    // Used to recalculate currentGradeintAngle
    double currentGradientAngle = gradientAngles(anchorPoint);
    double sx = cos(currentGradientAngle);
    double sy = sin(currentGradientAngle);
    double lineSegmentAngle = currentGradientAngle;

    cv::Point* point = new cv::Point(anchorPoint);

    std::list<cv::Point*>* currentLineSegment = new std::list<cv::Point*>;
    lineSegments.push_back(currentLineSegment);

    int mainDirection = getDirection(anchorPoint, gradientAngles);
    int subDirection = -1;
    bool stopWalk = false;

    // DEBUG
    double currentGradientMagnitude;

    do
    {
        // DEBUG
        currentGradientMagnitude = gradientMagnitudes(*point);

        // ####
        // Check if a new segment begins
        // ####
        currentGradientAngle = gradientAngles(*point);

        // currentGradientAngle is not in lineSegmentAngle's tolerance
        if(!isAligned(lineSegmentAngle, currentGradientAngle, angleTolerance))
        {
            currentLineSegment = new std::list<cv::Point*>;
            lineSegments.push_back(currentLineSegment);
        }

        if(subDirection == -1)
            currentLineSegment->push_front(point);
        else
            currentLineSegment->push_back(point);

        edgels(*point) = true;

        // ####
        // Recalculate the segment angle
        // ####
        sx += cos(currentGradientAngle);
        sy += sin(currentGradientAngle);
        lineSegmentAngle = atan(sy / sx);

        // ####
        // Find next point
        // ####
        point = findNextPoint(point, mainDirection, subDirection, gradientMagnitudes);

        // ####
        // Check if end reached, change direction if necessary or quit loop
        // ####
        if(gradientMagnitudes(*point) <= 0
           || getDirection(*point, gradientAngles) != mainDirection
           || edgels(*point)  != 0)
        {
            // Change direction
            if(subDirection == -1)
            {
                delete point;
                subDirection = 1;
                point = findNextPoint(&anchorPoint, mainDirection, subDirection, gradientMagnitudes);
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

bool EDL::getDirection(cv::Point& point, cv::Mat& gradientAngles)
{
    double angle = gradientAngles.ptr<double>(point.y)[point.x];

    if( fabs(cos(angle)) >= fabs(sin(angle)) )
    {
        return HORIZONTAL;
    }
    return VERTICAL;
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
    CV_Assert(compare <= 2 * M_PI && compare >= 0);
    CV_Assert(angle <= 2 * M_PI && angle >= 0);

    if(compare >= M_PI)
        compare -= M_PI;
    if(angle >= M_PI)
        angle -= M_PI;

    return ((angle - compare) <= tolerance) && ((angle - compare) >= -tolerance);
}
