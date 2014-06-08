#ifndef M_PI
#define M_PI 3.141592654
#endif
#include "linedetection/edl2/edl2.h"
#include "mathutil.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <iostream>

namespace formseher
{

EDL2::EDL2(int gaussianKernelSize, int minAnchorThreshold, int anchorStepping, int anchorThreshold, double angleTolerance, unsigned int minLineLength)
    : gaussianKernelSize(gaussianKernelSize),
      anchorThreshold(anchorThreshold),
      angleTolerance(angleTolerance),
      minLineLength(minLineLength),
      minAnchorThreshold(minAnchorThreshold),
      anchorStepping(anchorStepping)
{
}

EDL2::~EDL2(){}

std::vector<Line> EDL2::calculate(cv::InputArray _image)
{
    image = _image.getMat();
    std::vector<Line> result;

    if(!image.data)
        return result;

    //Definitions for grad, angle and anchor calculation
    gradientMagnitudes = cv::Mat::zeros(image.rows, image.cols, CV_8U);
    dx = cv::Mat::zeros(image.rows, image.cols, CV_16S);
    dy = cv::Mat::zeros(image.rows, image.cols, CV_16S);
    std::vector<cv::Point> anchors;

    // ####
    // use a filter algorithm to suppress noise
    // ####
    cv::Mat blur;
    cv::GaussianBlur(image, blur, cv::Size(gaussianKernelSize, gaussianKernelSize), 0, 0);
    image = blur;
    // ####
    // create gradient and direction output including the anchorpoints
    // ####

    calcGrad();
    findAnchors(anchors);

    // ####
    // run the routing algorithm
    // ####

    routeAnchors(anchors, result);

    // Save result
    return result;
}

void EDL2::findAnchors(std::vector<cv::Point> &anchors)
{
    bool direction;
    bool isAnchor = false;
    int nRows = gradientMagnitudes.rows-1;
    int nCols = gradientMagnitudes.cols-1;
    short center;

    for(int row = 1; row < nRows; row += anchorStepping)
    {
        uchar* gradMag = gradientMagnitudes.ptr<uchar>(row);

        for(int column = 1; column < nCols; column += anchorStepping)
        {
            if ((center = gradMag[column]) > minAnchorThreshold)  // check if the current Point might be an anchor
            {
                direction = getOrientation(*getSobelVector(row, column));
                if (direction == HORIZONTAL)
                {
                    if (center - (gradientMagnitudes.at<uchar>(row, column - 1)) >= anchorThreshold && center - (gradientMagnitudes.at<uchar>(row, column + 1) >= anchorThreshold ))
                    {
                        isAnchor = true;
                    }
                }
                if (direction == VERTICAL)
                {
                    if (center - (gradientMagnitudes.at<uchar>(row - 1, column)) >= anchorThreshold && center - (gradientMagnitudes.at<uchar>(row + 1, column) >= anchorThreshold ))
                    {
                        isAnchor = true;
                    }
                }
            }

            if(isAnchor) // save the Point
            {
                anchors.push_back(cv::Point(column, row));
                isAnchor = false;
            }
        }
    }
}

void EDL2::calcGrad()
{
    int nRows = gradientMagnitudes.rows-1;
    int nCols = gradientMagnitudes.cols-1;

    short sobelX[3][3] =   {{-1,0,1},
                            {-2,0,2},
                            {-1,0,1}};

    short sobelY[3][3] =   {{-1,-2,-1},
                            {0,0,0},
                            {1,2,1}};

    short Gx; // sobel value in X-Direction
    short Gy; // sobel value in Y-Direction
    short gradientMagnitude; // length of the vector[Gx,Gy]

    for(int row = 1; row < nRows; ++row)
    {
        uchar* gradMag = gradientMagnitudes.ptr<uchar>(row);
        short* gradDx = dx.ptr<short>(row);
        short* gradDy = dy.ptr<short>(row);

        for(int column = 1; column < nCols; ++column)
        {
            Gx =    (sobelX[0][0] * image.at<uchar>(row-1, column-1)) + (sobelX[0][1] * image.at<uchar>(row, column-1)) + (sobelX[0][2] * image.at<uchar>(row+1,column-1)) +
                    (sobelX[1][0] * image.at<uchar>(row-1, column))   + (sobelX[1][1] * image.at<uchar>(row, column))   + (sobelX[1][2] * image.at<uchar>(row+1,column)) +
                    (sobelX[2][0] * image.at<uchar>(row-1, column+1)) + (sobelX[2][1] * image.at<uchar>(row, column+1)) + (sobelX[2][2] * image.at<uchar>(row+1,column+1));

            Gy =    (sobelY[0][0] * image.at<uchar>(row-1, column-1)) + (sobelY[0][1] * image.at<uchar>(row, column-1)) + (sobelY[0][2] * image.at<uchar>(row+1,column-1)) +
                    (sobelY[1][0] * image.at<uchar>(row-1, column))   + (sobelY[1][1] * image.at<uchar>(row, column))   + (sobelY[1][2] * image.at<uchar>(row+1,column)) +
                    (sobelY[2][0] * image.at<uchar>(row-1, column+1)) + (sobelY[2][1] * image.at<uchar>(row, column+1)) + (sobelY[2][2] * image.at<uchar>(row+1,column+1));

            gradientMagnitude = math::sqrtFast(Gx*Gx + Gy*Gy);
            gradMag[column] = gradientMagnitude;
            gradDx[column] = Gx;
            gradDy[column] = Gy;
        }
    }
}

void EDL2::routeAnchors(std::vector<cv::Point>& anchorPoints, std::vector<Line> &result)
{
    std::vector<std::list<cv::Point*>*> lineSegments;

    // Iterate all anchor points
    for(auto anchorPoint : anchorPoints)
    {
        walkFromAnchor(anchorPoint, lineSegments);
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

void EDL2::walkFromAnchor(cv::Point& anchorPoint, std::vector<std::list<cv::Point*>*>& lineSegments)
{
    //save the results to
    std::list<cv::Point*>* currentLineSegment = new std::list<cv::Point*>;
    cv::Vec2s *currentLineVector;

    // two points to work with

    cv::Point *currentPoint = new cv::Point(anchorPoint);
    cv::Point *nextPoint;
    cv::Vec2s *nextVector;

    // Directions to walk to

    // HORIZONTAL
    cv::Point left = cv::Point(-1, 0);
    cv::Point right = cv::Point(1, 0);

    // VERTICAL
    cv::Point up = cv::Point(0, -1);
    cv::Point down =cv::Point(0, 1);

    int mainDirection; // VERTICAL or HORIZONTAL
    cv::Point subDirection; // left,rigt or up,down

    // ####
    // set defaults before we start walking
    // ####

    bool stopWalk = false;
    mainDirection = getOrientation(*getSobelVector(*currentPoint));

    if (mainDirection == HORIZONTAL)
    {
        subDirection = left;
    }

    if (mainDirection == VERTICAL)
    {
        subDirection = up;
    }

    currentLineSegment->push_back(currentPoint);
    currentLineVector = getSobelVector(*currentPoint);
    lineSegments.push_back(currentLineSegment);


    // ####
    // start walking
    // ####

    do
    {
        // gimmie the next point

        nextPoint = getNextPoint(*currentPoint, subDirection);
        nextVector = getSobelVector(*nextPoint);

        // ####
        // check if the point is worthy
        // ####

        if (nextPoint == currentPoint)
        {
            stopWalk = true;
        }
        else
        {
            //still same orientation and still usefull grad?
            if (mainDirection == getOrientation(*nextVector)
                    && gradientMagnitudes.at<uchar>(*nextPoint) > 0)
            {
                // check if the angle is in tolerance
                if(getAngleBetweenVectors(*currentLineVector, *nextVector) <= angleTolerance)
                {
                    if(subDirection == left || subDirection == up)
                    {
                        currentLineSegment->push_front(nextPoint);
                    }
                    else // right || down
                    {
                        currentLineSegment->push_back(nextPoint);
                    }
                }
                else // if the tolerance is exceeded
                {
                    currentLineSegment = new std::list<cv::Point*>;
                    currentLineSegment->push_back(nextPoint);
                    currentLineVector = getSobelVector(*nextPoint);
                    lineSegments.push_back(currentLineSegment);
                }
                currentPoint = nextPoint;
            }
            else
            {
                stopWalk = true;
            }
        }

        // ####
        // maybe we wanna swap directions...
        // ####

        if (stopWalk)
        {
            if (subDirection == left) // change from left to right
            {
                subDirection = right;
                *currentPoint = anchorPoint;
                stopWalk = false;
            }

            if (subDirection == up) // change from up to down
            {
                subDirection = down;
                *currentPoint = anchorPoint;
                stopWalk = false;
            }
        }

    } while(!stopWalk);
}

cv::Point* EDL2::getNextPoint(cv::Point& currentPoint, cv::Point& direction)
{
    int nRows;
    int nCols;
    int startRow = currentPoint.y;
    int startColumn = currentPoint.x;
    int curRow;
    int curCol;

    if (direction.y == 0) // HORIZONTAL
    {
        startRow -= 1;
        startColumn += direction.x;
        nRows = 3;
        nCols = 1;
    }
    if (direction.x == 0) // VERTICAL
    {
        startRow += direction.y;
        startColumn -= 1;
        nRows = 1;
        nCols = 3;
    }

    cv::Point* nextPoint = &currentPoint; //return the currentPoint if no nextPoint could be found
    uchar currentMag = 0;

    for(int i = 0 ; i < nRows; ++i)
    {
        curRow = startRow + i;
        uchar *gradMag = gradientMagnitudes.ptr<uchar>(curRow);

        for(int j = 0 ; j < nCols; ++j)
        {
            curCol = startColumn + j;

            // check if the move is still allowed
            if (!isOutOfBounds(curRow,curCol))
            {
                // check if mag is larger
                if (currentMag < gradMag[curCol])
                {
                    currentMag = gradMag[curCol];
                    nextPoint = new cv::Point(curCol, curRow);
                }
            }
        }
    }
    return nextPoint;
}

bool EDL2::isOutOfBounds(cv::Point &point)
{
    return isOutOfBounds(point.x, point.y);
}

bool EDL2::isOutOfBounds(int x, int y)
{
    return (x < 0) || (x > gradientMagnitudes.cols)
            || (y < 0) || (y > gradientMagnitudes.rows);
}

cv::Vec2s* EDL2::getSobelVector(cv::Point &point)
{
    return getSobelVector(point.y, point.x);
}

cv::Vec2s* EDL2::getSobelVector(int row, int column)
{
    return new cv::Vec2s(dx.at<short>(row, column), dy.at<short>(row, column));
}

bool EDL2::getOrientation(cv::Vec2s &v1)
{
    bool orientation = VERTICAL;

    if(abs(v1[0]) >= abs(v1[1]))
    {
        orientation = HORIZONTAL;
    }
    return orientation;

}

double EDL2::getAngleBetweenVectors(cv::Vec2s &v1, cv::Vec2s &v2)
{
    double cross = v1[0]*v2[1] - v1[1]*v2[0];
    double dot = v1.dot(v2);
    return atan2(cross, dot);
}
} // namespace formseher
