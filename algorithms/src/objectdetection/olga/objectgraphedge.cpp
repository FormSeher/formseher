#include "objectdetection/olga/objectgraphedge.h"

namespace formseher
{

ObjectGraphEdge::ObjectGraphEdge(ObjectGraphNode& start, ObjectGraphNode& end)
    : vector(end.getCoordinates() - start.getCoordinates()),
      start(start),
      end(end)
{
    distance = cv::norm(vector);
    cv::normalize(vector, vector);
}

int ObjectGraphEdge::getDistance() const
{
    return distance;
}

bool ObjectGraphEdge::operator==(const ObjectGraphEdge &rhs)
{
    if(vector != rhs.toCvVector())
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

cv::Vec2i ObjectGraphEdge::toCvVector() const
{
    return vector;
}

}
