#include "line.h"

namespace formseher
{

Line::Line(double x1, double y1, double x2, double y2)
    : start(x1, y1),
      end(x2, y2)
{

    directionVector[0] = end.x - start.x;
    directionVector[1] = end.y - start.y;
}

Line::Line(const cv::Point2d& start, const cv::Point2d& end)
    : Line(start.x, start.y, end.x, end.y)
{
}

Line::~Line()
{
}

const cv::Point2d& Line::getStart()
{
    return start;
}

const cv::Point2d& Line::getEnd()
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

const double getLength()
{

}

}
