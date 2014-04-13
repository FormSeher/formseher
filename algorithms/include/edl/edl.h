#ifndef EDL_H
#define EDL_H

#include "algorithm.h"

#include "line.h"

#include <opencv2/core/core.hpp>
#include <vector>
#include <list>

#define HORIZONTAL 0
#define VERTICAL   1

class EDL : public Algorithm
{
public:
    EDL();
    ~EDL();

    void calculate();

private:
    void calcGradAngleAnchors(cv::InputArray gradientX, cv::InputArray gradientY, cv::OutputArray gradientMagnitude, cv::OutputArray gradientAngle, std::vector<cv::Point>& anchors);

    bool isAnchor(cv::Mat& src, int x, int y);

    void routeAnchors(cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*> result);

    void routeAnchors(double angleTolerance, cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point2i*>& anchorPoints, std::vector<Line*>& result);

    void walkFromAnchor(cv::Point& anchorPoint, double angleTolerance, cv::Mat_<uchar>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<bool> &edgels, std::vector<std::list<cv::Point*>*>& lineSegments);

    bool getDirection(cv::Point& point, cv::Mat& gradientAngles);

    cv::Point* findNextPoint(cv::Point* currentPoint, int mainDirection, int subDirection, cv::Mat_<uchar>& gradientMagnitudes);

    bool isAligned(double compare, double angle, double tolerance);

    int ksize;
    double scale;
    double delta;
    int threshold;
};

#endif // EDL_H
