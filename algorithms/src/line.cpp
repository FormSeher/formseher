#include "line.h"

Line::Line(double x1, double y1, double x2, double y2)
    : start(x1, y1),
      end(x2, y2)
{
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
