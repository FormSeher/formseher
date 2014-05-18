#include "objectdetection/olga/objectgraphedge.h"

namespace formseher
{

ObjectGraphEdge::ObjectGraphEdge(ObjectGraphNode& start, ObjectGraphNode& end)
    : cv::Vec2i(end.getCoordinates() - start.getCoordinates()),
      start(start),
      end(end)
{
    distance = cv::norm(*static_cast<cv::Vec2i*>(this));
    cv::normalize(*this, *this);
}

int ObjectGraphEdge::getDistance() const
{
    return distance;
}

bool ObjectGraphEdge::operator==(const ObjectGraphEdge &rhs)
{
    if(static_cast<cv::Vec2i>(*this) != static_cast<cv::Vec2i>(rhs))
        return false;
    if(this->getDistance() != rhs.getDistance())
        return false;
    return true;
}

bool ObjectGraphEdge::operator!=(const ObjectGraphEdge &rhs)
{
    return !((*this) == rhs);
}

ObjectGraphNode& ObjectGraphEdge::getStart() const
{
    return start;
}

ObjectGraphNode& ObjectGraphEdge::getEnd() const
{
    return end;
}

}
