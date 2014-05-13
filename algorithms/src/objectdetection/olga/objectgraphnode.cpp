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
