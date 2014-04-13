#ifndef EDL_H
#define EDL_H

#include "algorithm.h"

#include "line.h"

#include <opencv2/core/core.hpp>
#include <vector>

class EDL : public Algorithm
{
public:
    EDL();
    ~EDL();

    void calculate();

private:
    void EDL::calcGradAngleAnchors(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle, std::vector<cv::Point> anchors);

    bool EDL::isAnchor(cv::Mat& src, int x, int y);

    void routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*> result);

    int ksize;
    double scale;
    double delta;
    int threshold;
    cv::Mat src;
};

#endif // EDL_H
