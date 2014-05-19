#include "objectdetection/olga/objectgraphnode.h"

namespace formseher
{

ObjectGraphNode::ObjectGraphNode(int x, int y)
    : coordinates(x, y)
{
}

void ObjectGraphNode::addEdge(const ObjectGraphEdge* edge)
{
    edges.push_back(edge);
}

const std::vector<const ObjectGraphEdge*> &ObjectGraphNode::getEdges() const
{
    return edges;
}

bool ObjectGraphNode::operator==(const ObjectGraphNode &rhs) const
{
    return this->getCoordinates() == rhs.getCoordinates();
}

bool ObjectGraphNode::operator<(const ObjectGraphNode &rhs) const
{
    return this->getCoordinates().y < rhs.getCoordinates().y
            || this->getCoordinates().x < rhs.getCoordinates().x;
}

cv::Point2i ObjectGraphNode::getCoordinates() const
{
    return coordinates;
}

}
