#ifndef OBJECT_H
#define OBJECT_H

#include <opencv2/core/core.hpp>
#include <string.h>
#include "line.h"

namespace formseher {

class Object
{

public:
    Object();
    ~Object();

    void addLine(const Line line);
    const std::vector<const Line*>& getLines() const;

    cv::Rect getBoundingBox() const;

    void setName(std::string name);
    std::string getName() const;

private:
    void updateBoundingBox(const cv::Point2i& point);
    cv::Point2i boundingBoxCorners[2];

    std::string name;
    std::vector<const Line*> lines;

};

}   // formseher

#endif // OBJECT_H
