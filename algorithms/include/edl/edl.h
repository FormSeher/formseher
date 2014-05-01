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
    EDL(int sobelKernelSize = 3, double sobelScale = 1.9, double sobelDelta = 0.0, int gaussianKernelSize = 3,
        int anchorThreshold = 36, double angleTolerance = 22.5 * M_PI / 180.0);
    ~EDL();

    std::vector<Line> calculate(cv::InputArray _image);

private:
    void calcGradAngleAnchors(cv::InputArray _gradientX, cv::InputArray _gradientY, cv::OutputArray _gradientMagnitudes, cv::OutputArray _gradientAngles, std::vector<cv::Point>& anchors);

    bool isAnchor(cv::Mat& src, int row, int column);

    void routeAnchors(double angleTolerance, cv::InputArray magnitudes, cv::InputArray angles, std::vector<cv::Point>& anchorPoints, std::vector<Line>& result);

    void walkFromAnchor(cv::Point& anchorPoint, double angleTolerance, cv::Mat_<uchar>& gradientMagnitudes, cv::Mat_<double>& gradientAngles, cv::Mat_<uchar> &edgels, std::vector<std::list<cv::Point*>*>& lineSegments);

    bool getDirection(double angle);

    cv::Point* findNextPoint(cv::Point* currentPoint, int mainDirection, int subDirection, cv::Mat_<uchar>& gradientMagnitudes);

    bool isAligned(double compare, double angle, double tolerance);

    bool isOutOfBounds(cv::Point* point, cv::InputArray matrix);

    int sobelKernelSize;
    double sobelScale;
    double sobelDelta;
    int gaussianKernelSize;
    int anchorThreshold;
    double angleTolerance;
};

#endif // EDL_H
