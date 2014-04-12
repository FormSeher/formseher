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


void EDL::calcGradAndAngle(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle)
{

}

void EDL::calculateAnchors(cv::InputArray gradientMagnitude, cv::OutputArray anchorPoints, int threshold)
{

}

void EDL::routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*> result)
{

}
