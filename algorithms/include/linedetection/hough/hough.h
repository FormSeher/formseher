/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

#ifndef FS_HOUGH_H
#define FS_HOUGH_H

#include "linedetection/linedetectionalgorithm.h"

#include "line.h"

#include <opencv2/core/core.hpp>
#include <vector>
#include <list>

#if defined(_WIN32)

#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef unsigned int uint;

#endif

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


class Hough : public LineDetectionAlgorithm
{
public:

    /**
     * @brief hough line detection constructor
     * @param checkEnvironmentSize : size of environment around points to be searched for start and end of lines
     * @param maximalLineGap : maximum gap between two lines in order to be considered as one line
     * @param minimumLineSize : minimum line length -> smaller lines will not be returned
     */
    Hough(u_int16_t checkEnvironmentSize = 2, u_int16_t maximalLineGap = 9, u_int16_t minimumLineSize = 30);
    ~Hough();

    /*! @copydoc LineDetectionAlgorithm::calculate()
     */
    std::vector<Line> calculate(cv::InputArray _image);

private:

    /**
     * @brief check environment of one point in order to know if there is a possible start- or endpoint or linepoint
     * @param inputMatrix : canny edge picture
     * @param currX : x value of point to check
     * @param currY : y value of point to check
     * @return true if in environment of checked point is a canny edge
     */
    bool checkEnvironmentInRightAngle(cv::Mat& inputMatrix, double currX, double currY);

    /**
     * @brief calculate minVotes for hough transformation automatically
     * @param inputCannyEdgePixelDensity : factor of all pixels / edge pixels
     * @param inputEdgePixelCounter : number of edge pixels
     * @return minVotes for hough transformation
     */
    u_int16_t calculateMinimalVotes(u_int16_t inputCannyEdgePixelDensity, u_int16_t inputEdgePixelCounter);

    /**
     * @brief calculate greatest common divisor of two numbers
     * @param a : number1
     * @param b : number2
     * @return return gcd
     */
    u_int32_t calculateGreatestCommonDivisor(u_int32_t a, u_int32_t b);

    /**
     * @brief compare hough line with canny edge picture in order to receive start and endpoint of hough line
     * @param outputLines : vector that new lines with start and endpoints are stored in
     * @param inputLines : lines received from hough transformation
     * @param inputCannyImage
     */
    void compareHoughLinesWithCannyEdges(std::vector<Line>& outputLines, std::vector<cv::Vec2f>& inputLines, cv::Mat& inputCannyImage);

    /**
     * @brief create a canny edge image. This method also autoadjusts canny parameters in order to receive a propper result.
     * @param outputCannyImage : image canny result is stored in
     * @param inputGrayLevelImage : graylevel input image
     */
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

#endif // FS_HOUGH_H
