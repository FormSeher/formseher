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

const cv::Vec2i Line::getPositionVector()
{
    return cv::Vec2i(start.x, start.y);
}

const cv::Vec2i& Line::getDirectionVector()
{
    return directionVector;
}

double Line::getLength()
{
    return length;
}

} // namespace formseher
