#include "edl/edl.h"

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

void calcGradAndAngle(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle)
{

}

void calculateAnchors(cv::InputArray gradientMagnitude, cv::OutputArray anchorPoints, int threshold)
{

}

void routeAnchors(cv::InputArray gradientMagnitude, cv::InputArray gradientAngle, cv::InputArray anchorPoints, std::vector<Line*> result)
{

}
