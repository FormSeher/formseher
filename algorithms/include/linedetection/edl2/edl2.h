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

#ifndef FS_EDL2_H
#define FS_EDL2_H

#ifndef M_PI
#define M_PI 3.141592654
#endif

#include "linedetection/linedetectionalgorithm.h"

#include "line.h"

#include "mathutil.h"

#include <opencv2/core/core.hpp>
#include <vector>
#include <list>

#define HORIZONTAL 0
#define VERTICAL   1

namespace formseher
{

class EDL2 : public LineDetectionAlgorithm
{

public:

    EDL2(int gaussianKernelSize = 3, int minAnchorThreshold = 20, int anchorStepping = 3, int anchorThreshold = 30, double angleTolerance = 22.5 *  M_PI / 180.0, unsigned int minLineLength = 30);

    ~EDL2();

    std::vector<Line> calculate(cv::InputArray _image);

private:

    /**
    * @brief calculates the gradientMagnitudes for the the given image
    */

    void calcGrad();

    /**
    * @brief finds the anchorpoints in the calculated edge image
    * @param Vector to save the found anchorpoints to
    */

    void findAnchors(std::vector<cv::Point> &anchors);

    /**
    * @brief connects the found anchors with another
    * @param Vector with found anchors
    * @param Vector to save found lines to
    */

    void routeAnchors(std::vector<cv::Point>& anchorPoints, std::vector<Line> &result);

    /**
    * @brief walks from given point to the next point and saves the routed points as a lineSegment.
    * @param Point to start walking from
    * @param Vector with all found lineSegments
    */

    void walkFromAnchor(cv::Point& anchorPoint, std::vector<std::list<cv::Point*>*>& lineSegments);

    /**
    * @brief tells if the orientation of a given vector is HORIZONTAL or VERTICAL
    * @param Vector
    * @param Vector with all found lineSegments
    */

    bool getOrientation(cv::Vec2s v1);

    /**
    * @brief finds the nextPoint to walk to, considering the orientation.
    * @param Point to start the search for a possible nextPoint
    * @param Point object for the chosen subdirection left/right/up/down
    * @return Point the nextPoint. If no adeauqte nextPoint is found the given point is returned.
    */

    cv::Point* getNextPoint(cv::Point& currentPoint, cv::Point& subDirection);

    /**
    * @brief checks if the point is still in the image
    * @param Point to check
    * @return bool value
    */

    bool isOutOfBounds(cv::Point &point);

    /**
    * @brief checks if the point is still in the image
    * @param Integer coordinate of the x value
    * @param Integer coordinate of the y value
    * @return bool value
    */

    bool isOutOfBounds(int row, int col);

    /**
    * @brief helper method to get the the vector from the sobel image
    * @param Point for which the vector is needed
    * @return Vector of the given point
    */

    cv::Vec2s getSobelVector(cv::Point &point);

    /**
    * @brief helper method to get the the vector from the sobel image
    * @param Integer value of row
    * @param Integer value of column
    * @return Vector of the given coordinate
    */

    cv::Vec2s getSobelVector(int row, int column);

    /**
    * @brief gets the angle beetween two vectors as radiant value
    * @param Vector one
    * @param Vector two
    * @return Double value of the calculated radiant value
    */

    double getAngleBetweenVectors(cv::Vec2s &v1, cv::Vec2s &v2);

    int gaussianKernelSize;
    int anchorThreshold;
    double angleTolerance;
    unsigned int minLineLength;
    int minAnchorThreshold;
    int anchorStepping;
    cv::Mat image;
    cv::Mat gradientMagnitudes;
    cv::Mat dx;
    cv::Mat dy;
};
} // namespace formseher

#endif // FS_EDL2_H
