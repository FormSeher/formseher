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

#ifndef FS_LINE_H
#define FS_LINE_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class Line
{
public:
    /**
     * @brief Constructs line from given coordinates.
     * @param x1 x-coordinate of one end.
     * @param y1 y-coordinate of one end.
     * @param x2 x-coordinate of other end.
     * @param y2 y-coordinate of other end.
     */
    Line(int x1, int y1, int x2, int y2);

    /**
     * @brief Creates a line from given points.
     * @param start One end of the line.
     * @param end Other end of the line.
     */
    Line(const cv::Point2i& start, const cv::Point2i& end);

    /**
     * Standard desturctor.
     */
    ~Line();

    /**
     * @brief Get one end of the line.
     * @return One end of the line.
     */
    const cv::Point2i& getStart() const;

    /**
     * @brief Get other end of the line.
     * @return Other end of the line.
     */
    const cv::Point2i& getEnd() const;

    /**
     * @brief Get point used as start for perpendicular line format.
     * @return Perpenicular point.
     */
    const cv::Point2i& getPerpendicularPoint() const;

    /**
     * @brief Get center of the line which lies centered between start and end.
     * @return Center point
     */
    const cv::Point2d& getCenterPoint() const;

    /**
     * @brief Get the position vector used by vector line format.
     * @return Position vector.
     */
    const cv::Vec2i getPositionVector() const;

    /**
     * @brief Get direction vector used by vector line format.
     * @return Direction vector.
     */
    const cv::Vec2d &getDirectionVector() const;

    /**
     * @brief Get length of line.
     * @return Length of line.
     */
    double getLength() const;

    /**
     * @brief Get the distance of perpendicular point to the coordinate system's origin.
     * @return Distance of perpendicular point to origin.
     */
    double getPerpendicularDistanceToOrigin();

    /**
     * @brief Get the distance of start point to perpendicular point.
     * @return Distance of start and perpendicular point.
     */
    double getPerpendicularDistanceToStart();

    /**
     * @brief get the distance of end and perpendicular point.
     * @return Distance of end and perpendicular point.
     */
    double getPerpendicularDistanceToEnd();

    /**
     * @brief Equals operator.
     * @param line The line compared to this.
     * @return True if both lines are equal.
     */
    bool operator==(const Line& line) const;

    /**
     * @brief Set parameters for perpendicular line format.
     *
     * Can be used to easily set these parameters e.g. if they are saved elsewhere. Saves some computation time.
     *
     * @param perpendicularDistanceToOrigin The distance of perpendicular point to coordinate system's origin.
     * @param perpendicularPoint The perpendicular point.
     */
    void setPerpendicular(double perpendicularDistanceToOrigin, cv::Point2i& perpendicularPoint);

    /**
     * @brief Switches start and end points and all vectors which depend on them.
     */
    void switchStartAndEnd() ;

private:
    cv::Point2i start;
    cv::Point2i end;
    cv::Point2i perpendicularPoint;
    cv::Point2d centerPoint;

    cv::Vec2d directionVector;

    double perpendicularDistanceToOrigin;
    double perpendicularDistanceToStart;
    double perpendicularDistanceToEnd;

    double length;

    bool perpendicularAlreadyDone = false;

    /**
     * @brief Calcualtes parameters for perpendicular line format.
     */
    void calculatePerpendicular();
};

}

#endif // FS_LINE_H
