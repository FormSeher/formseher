#ifndef FS_LINE_H
#define FS_LINE_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class Line
{
public:
    Line(double x1, double y1, double x2, double y2);

    Line(const cv::Point2d& start, const cv::Point2d& end);

    ~Line();

    const cv::Point2d& getStart();
    const cv::Point2d& getEnd();

    const cv::Vec2i getPositionVector();
    const cv::Vec2i& getDirectionVector();
    const double getLength();

private:
    cv::Point2d start;
    cv::Point2d end;

    cv::Vec2i directionVector;
    double length;

};

}

#endif // FS_LINE_H
