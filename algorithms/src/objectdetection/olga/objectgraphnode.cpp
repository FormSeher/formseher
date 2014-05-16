#include "objectdetection/olga/objectgraphnode.h"

ObjectGraphNode::ObjectGraphNode(int x, int y)
    : cv::Point2i(x, y)
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

bool ObjectGraphNode::operator<(const ObjectGraphNode &rhs)
{
    return this->y < rhs.y || this->x < rhs.x;
}
