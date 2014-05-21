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

    const std::vector<Line>& getLines() const;
    cv::Rect getBoundingBox() const;
    std::string getName() const;
    void addLine(Line* line);
    void setName(std::string name);

private:

    cv::Rect boundingBox;
    std::string name;
    std::vector<Line*> lines;

};

}   // formseher

#endif // OBJECT_H
