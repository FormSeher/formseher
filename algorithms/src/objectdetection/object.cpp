#include "objectdetection/object.h"

namespace formseher
{

Object::Object()
{

}

const std::vector<const Line*> &Object::getLines() const
{
    return lines;
}

cv::Rect Object::getBoundingBox() const
{
    return cv::Rect(
            boundingBoxCorners[0].x, // x
            boundingBoxCorners[0].y, // y
            boundingBoxCorners[1].x - boundingBoxCorners[0].x, // width
            boundingBoxCorners[1].y - boundingBoxCorners[0].y  // height
            );
}

void Object::addLine(const Line* line)
{
    lines.push_back(line);

    // update bounding box. First check is needed for the first inserted
    // corner of the bounding box.
    if(lines.size() == 1)
    {
        boundingBoxCorners[0] = line->getStart();
        boundingBoxCorners[1] = line->getEnd();
    }
    else
        updateBoundingBox(line->getStart());

    updateBoundingBox(line->getEnd());
}

void Object::setName(std::string name)
{
    this->name = name;
}

std::string Object::getName() const
{
    return name;
}

void Object::updateBoundingBox(const cv::Point2i& point)
{
    // Update x coordinate
    if(boundingBoxCorners[0].x > point.x)
        boundingBoxCorners[0].x = point.x;
    else if(boundingBoxCorners[1].x < point.x)
        boundingBoxCorners[1].x = point.x;

    // Update y coordinate
    if(boundingBoxCorners[0].y > point.y)
        boundingBoxCorners[0].y = point.y;
    else if(boundingBoxCorners[1].y < point.y)
        boundingBoxCorners[1].y = point.y;
}

} // namespace formseher
