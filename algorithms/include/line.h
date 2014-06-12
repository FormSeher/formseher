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
    const cv::Point2i& getPerpendicularPoint() const;

    const cv::Vec2i getPositionVector() const;
    const cv::Vec2d &getDirectionVector() const;

    double getLength() const;
    double getPerpendicularDistanceToOrigin();
    double getPerpendicularDistanceToStart();
    double getPerpendicularDistanceToEnd();


    void setPerpendicular(double perpendicularDistanceToOrigin, cv::Point2i& perpendicularPoint);

private:
    cv::Point2i start;
    cv::Point2i end;
    cv::Point2i perpendicularPoint;

    cv::Vec2d directionVector;

    double perpendicularDistanceToOrigin;
    double perpendicularDistanceToStart;
    double perpendicularDistanceToEnd;

    double length;

    bool perpendicularAlreadyDone = false;

    void calculatePerpendicular();
};

}

#endif // FS_LINE_H
