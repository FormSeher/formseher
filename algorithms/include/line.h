#ifndef LINE_H
#define LINE_H

#include <opencv2/core/core.hpp>

class Line
{
public:
    Line(double x1, double y1, double x2, double y2);

    Line(const cv::Point2d& start, const cv::Point2d& end);

    ~Line();

    const cv::Point2d& getStart();
    const cv::Point2d& getEnd();

private:
    cv::Point2d start;
    cv::Point2d end;
};

#endif // LINE_H
