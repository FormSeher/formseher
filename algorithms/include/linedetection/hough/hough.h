#ifndef HOUGH_H
#define HOUGH_H

#include "linedetection/algorithm.h"

#include "line.h"

#include <opencv2/core/core.hpp>
#include <vector>
#include <list>

namespace formseher
{

// OpenCV ###############

#define halfPi ((float)(CV_PI*0.5))
#define Pi     ((float)CV_PI)
#define a0  0 /*-4.172325e-7f*/   /*(-(float)0x7)/((float)0x1000000); */
#define a1 1.000025f        /*((float)0x1922253)/((float)0x1000000)*2/Pi; */
#define a2 -2.652905e-4f    /*(-(float)0x2ae6)/((float)0x1000000)*4/(Pi*Pi); */
#define a3 -0.165624f       /*(-(float)0xa45511)/((float)0x1000000)*8/(Pi*Pi*Pi); */
#define a4 -1.964532e-3f    /*(-(float)0x30fd3)/((float)0x1000000)*16/(Pi*Pi*Pi*Pi); */
#define a5 1.02575e-2f      /*((float)0x191cac)/((float)0x1000000)*32/(Pi*Pi*Pi*Pi*Pi); */
#define a6 -9.580378e-4f    /*(-(float)0x3af27)/((float)0x1000000)*64/(Pi*Pi*Pi*Pi*Pi*Pi); */

#define _sin(x) ((((((a6*(x) + a5)*(x) + a4)*(x) + a3)*(x) + a2)*(x) + a1)*(x) + a0)
#define _cos(x) _sin(halfPi - (x))

// OpenCV ###############

#define ABS_X_GREATER_Y  1
#define ABS_X_LOWER_Y    2
#define ABS_X_EQUAL_Y    0


class Hough : public Algorithm
{
public:
    Hough(u_int16_t checkEnvironmentSize = 2, u_int16_t maximalLineGap = 9, u_int16_t minimumLineSize = 30);
    ~Hough();

    std::vector<Line> calculate(cv::InputArray _image);

private:

    bool checkEnvironmentInRightAngle(cv::Mat& inputMatrix, double currX, double currY);

    u_int16_t calculateMinimalVotes(u_int16_t inputCannyEdgePixelDensity, u_int16_t inputEdgePixelCounter);

    u_int32_t calculateGreatestCommonDivisor(u_int32_t a, u_int32_t b);

    void compareHoughLinesWithCannyEdges(std::vector<Line>& outputLines, std::vector<cv::Vec2f>& inputLines, cv::Mat& inputCannyImage);

    void getCannyImage(cv::Mat& outputCannyImage, cv::Mat& inputGrayLevelImage);

    cv::Vec2i lineDirection;
    u_int8_t lineOrientation;
    u_int16_t checkEnvironmentSize; // FROM_GUI
    u_int16_t imageDiagonal;
    u_int16_t maximalLineGap;       // FROM_GUI
    u_int16_t minimalHoughVotes;
    u_int16_t minimumLineSize;      // FROM_GUI

};

} // namespace formseher

#endif // HOUGH_H
