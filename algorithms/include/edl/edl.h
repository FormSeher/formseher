#ifndef EDL_H
#define EDL_H

#include "algorithm.h"

#include "line.h"

#include <opencv2/core/core.hpp>
#include <vector>

#define HORIZONTAL 0
#define VERTICAL   1

class EDL : public Algorithm
{
public:
    EDL();
    ~EDL();

    void calculate();

private:
    void calcGradAndAngle(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle);

    void calculateAnchors(cv::InputArray gradientMagnitude, cv::OutputArray anchorPoints, int threshold);

    void routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*> result);

    bool getDirection(cv::Point& point, cv::Mat& gradientAngles);
};

#endif // EDL_H
