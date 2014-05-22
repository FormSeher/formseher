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

    const cv::Point2d& getStart() const;
    const cv::Point2d& getEnd() const;

private:
    cv::Point2d start;
    cv::Point2d end;
};

}

#endif // FS_LINE_H
