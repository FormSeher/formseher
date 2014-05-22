#include "line.h"

namespace formseher
{

Line::Line(int x1, int y1, int x2, int y2)
    : start(x1, y1),
      end(x2, y2)
{
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

}
