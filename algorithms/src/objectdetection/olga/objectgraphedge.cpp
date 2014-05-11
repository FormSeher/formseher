#include "objectdetection/olga/objectgraphedge.h"

#include "mathutil.h"

ObjectGraphEdge::ObjectGraphEdge(const ObjectGraphNode& start, const ObjectGraphNode& end)
    : cv::Vec2i(end - start)
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
