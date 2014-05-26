#ifndef FS_LINE_H
#define FS_LINE_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class Line
{
public:
    Line(int x1, int y1, int x2, int y2);

    Line(const cv::Point2i& start, const cv::Point2i& end);

    ~Line();

    const cv::Point2i& getStart() const;
    const cv::Point2i& getEnd() const;

    const cv::Vec2i getPositionVector();
    const cv::Vec2i& getDirectionVector();

    double getLength();

private:
    cv::Point2i start;
    cv::Point2i end;

    cv::Vec2i directionVector;
    double length;
};

}

#endif // FS_LINE_H
