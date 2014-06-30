#include "line.h"

namespace formseher
{

Line::Line(int x1, int y1, int x2, int y2)
    : start(x1, y1),
      end(x2, y2)
{
    //Calculate direction vector
    directionVector[0] = end.x - start.x;
    directionVector[1] = end.y - start.y;

    //Calculate length of line
    length = cv::norm(directionVector);

    //Normalize line to length 1
    directionVector = cv::normalize(directionVector);

    // Calculate center point
    centerPoint.x = (x1 + x2) / 2.0;
    centerPoint.y = (y1 + y2) / 2.0;
}

Line::Line(const cv::Point2i& start, const cv::Point2i& end)
    : Line(start.x, start.y, end.x, end.y)
{
}

Line::~Line()
{
}

const cv::Point2i& Line::getStart() const
{
    return start;
}

const cv::Point2i& Line::getEnd() const
{
    return end;
}

const cv::Vec2i Line::getPositionVector() const
{
    return cv::Vec2i(start.x, start.y);
}

const cv::Vec2d& Line::getDirectionVector() const
{
    return directionVector;
}

double Line::getLength() const
{
    return length;
}

void Line::switchStartAndEnd()
{
    cv::Point2i newEnd = start;
    start = end;
    end = newEnd;

    directionVector[0] = -directionVector[0];
    directionVector[1] = -directionVector[1];
}

double Line::getPerpendicularDistanceToOrigin()
{
    if( ! perpendicularAlreadyDone )
        calculatePerpendicular();

    return perpendicularDistanceToOrigin;
}

double Line::getPerpendicularDistanceToStart()
{
    if( ! perpendicularAlreadyDone )
        calculatePerpendicular();

    return perpendicularDistanceToStart;
}

double Line::getPerpendicularDistanceToEnd()
{
    if( ! perpendicularAlreadyDone )
        calculatePerpendicular();

    return perpendicularDistanceToEnd;
}

const cv::Point2i& Line::getPerpendicularPoint() const
{
    if( ! perpendicularAlreadyDone )
        ((Line*)this)->calculatePerpendicular();

    return perpendicularPoint;
}

const cv::Point2d &Line::getCenterPoint() const
{
    return centerPoint;
}

void Line::setPerpendicular(double perpendicularDistance, cv::Point2i& perpendicularPoint)
{
    this->perpendicularDistanceToOrigin = perpendicularDistance;
    this->perpendicularPoint = perpendicularPoint;

    perpendicularDistanceToStart = cv::norm(start - perpendicularPoint);
    perpendicularDistanceToEnd = cv::norm(end - perpendicularPoint);

    perpendicularAlreadyDone = true;
}

void Line::calculatePerpendicular()
{
    double lambda = - ( (double)start.x * (end.x - start.x) + start.y * (end.y - start.y) ) /
                      ( (end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y) );

    perpendicularPoint.x = start.x + lambda * (end.x - start.x);
    perpendicularPoint.y = start.y + lambda * (end.y - start.y);

    perpendicularDistanceToOrigin = cv::norm(perpendicularPoint);

    perpendicularDistanceToStart = cv::norm(start - perpendicularPoint);
    perpendicularDistanceToEnd = cv::norm(end - perpendicularPoint);

    perpendicularAlreadyDone = true;
}

bool Line::operator==(const Line& line) const
{
    return (this->start == line.getStart() && this->end == line.getEnd()) ||
           (this->start == line.getEnd() && this->end == line.getStart()) ;
}


} // namespace formseher

