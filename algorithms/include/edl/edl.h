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
    void calcGradAndAngle(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle);

    void calculateAnchors(cv::InputArray gradientMagnitude, cv::OutputArray anchorPoints, int threshold);

    void routeAnchors(cv::InputArray gradientMagnitude, cv::InputArray gradientAngle, cv::InputArray anchorPoints, std::vector<Line*> result);
};

#endif // EDL_H
