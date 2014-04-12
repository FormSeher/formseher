#include "edl/edl.h"

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

EDL::EDL()
{

}

EDL::~EDL()
{

}

void EDL::calculate()
{
    // call calcgradAndAngle
    // call calculateAnchors
    // call routeAnchors
    // Save result
}


void EDL::calcGradAndAngle(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle)
{

}

void EDL::calculateAnchors(cv::InputArray gradientMagnitude, cv::OutputArray anchorPoints, int threshold)
{

}

void EDL::routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*>& result)
{
    CV_Assert(magnitudes.type() == CV_64F && angles.type() == CV_64F);

    cv::Mat_<double> gradientMagnitudes = magnitudes.getMat();
    cv::Mat_<double> gradientAngles = angles.getMat();
    cv::Mat_<bool> edgels = cv::Mat::zeros(gradientMagnitudes.rows, gradientMagnitudes.cols, CV_8U);
    std::vector<std::vector<cv::Point*>*> lineSegments;

    // Iterate all anchor points
    for(auto anchorPoint : anchorPoints)
    {
        // Is the pixel already part of an edge?
        if(edgels(*anchorPoint) != 0)
        {
            continue;
        }

        walkFromAnchor(*anchorPoint, gradientMagnitudes, gradientAngles, edgels, lineSegments);
    }

    // Create result
    for(auto lineSegment : lineSegments)
    {
        Line* line = new Line(**lineSegment->begin(), **lineSegment->end());
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

void EDL::walkFromAnchor(cv::Point& anchorPoint, cv::Mat_<double>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<bool> &edgels, std::vector<std::vector<cv::Point*>*>& lineSegments)
{
    // TODO: Make this a parameter
    double angleTolerance = 0.1;

    // Used to recalculate currentGradeintAngle
    double currentGradientAngle = gradientAngles(anchorPoint);
    double sx = cos(currentGradientAngle);
    double sy = sin(currentGradientAngle);
    double lineSegmentAngle = currentGradientAngle;

    cv::Point* point = new cv::Point(anchorPoint);

    std::vector<cv::Point*>* currentLineSegment = new std::vector<cv::Point*>;
    lineSegments.push_back(currentLineSegment);

    int mainDirection = getDirection(anchorPoint, gradientAngles);
    int subDirection = -1;
    bool stopWalk = false;

    do
    {
        // ####
        // Check if a new segment begins
        // ####
        currentGradientAngle = gradientAngles(*point);

        // currentGradientAngle is not in lineSegmentAngle's tolerance
        if(lineSegmentAngle + angleTolerance < currentGradientAngle
           || lineSegmentAngle - angleTolerance > currentGradientAngle)
        {
            currentLineSegment = new std::vector<cv::Point*>;
            lineSegments.push_back(currentLineSegment);
        }

        currentLineSegment->push_back(point);

        // ####
        // Recalculate the segment angle
        // ####
        sx += cos(currentGradientAngle);
        sy += sin(currentGradientAngle);
        lineSegmentAngle = atan(sy / sx);

        // ####
        // Find next point
        // ####
        if(mainDirection == HORIZONTAL)
        {
            if(   gradientMagnitudes(point->x + subDirection, point->y + 1) > gradientMagnitudes(point->x + subDirection, point->y)
               && gradientMagnitudes(point->x + subDirection, point->y + 1) > gradientMagnitudes(point->x + subDirection, point->y - 1))
            {
                point = new cv::Point(point->x + subDirection, point->y + 1);
            }
            else if (gradientMagnitudes(point->x + subDirection, point->y)  > gradientMagnitudes(point->x + subDirection, point->y - 1))
            {
                point = new cv::Point(point->x + subDirection, point->y);
            }
            else
            {
                point = new cv::Point(point->x + subDirection, point->y - 1);
            }
        }
        // VERTICAL
        else
        {
            if(   gradientMagnitudes(point->x + 1, point->y + subDirection) > gradientMagnitudes(point->x,     point->y + subDirection)
               && gradientMagnitudes(point->x + 1, point->y + subDirection) > gradientMagnitudes(point->x - 1, point->y + subDirection))
            {
                point = new cv::Point(point->x + 1, point->y + subDirection);
            }
            else if (gradientMagnitudes(point->x, point->y + subDirection)  > gradientMagnitudes(point->x - 1, point->y + subDirection))
            {
                point = new cv::Point(point->x, point->y + subDirection);
            }
            else
            {
                point = new cv::Point(point->x - 1, point->y + subDirection);
            }
        }

        // ####
        // Check if end reached, change direction if necessary or quit loop
        // ####
        if(gradientMagnitudes(*point) <= 0
           || getDirection(*point, gradientAngles) != mainDirection
           || edgels(*point)  != 0)
        {
            // Change direction
            if(subDirection == -1)
                subDirection = 1;
            // Already examined both directions so let's quit
            else
            {
                delete point;
                stopWalk = true;
            }
        }
    } while(!stopWalk);
}

bool EDL::getDirection(cv::Point& point, cv::Mat& gradientAngles)
{
    double angle = gradientAngles.ptr<double>(point.x)[point.y] * M_PI / 180.0d;

    if( fabs(cos(angle)) >= fabs(sin(angle)) )
    {
        return HORIZONTAL;
    }
    return VERTICAL;
}
