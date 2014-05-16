#include "objectdetection/olga/objectgraph.h"

ObjectGraph::ObjectGraph()
{
}

ObjectGraph::~ObjectGraph()
{
    for(auto node : nodes)
        delete node;
    for(auto edge : edges)
        delete edge;
}

float ObjectGraph::compareTo(const ObjectGraph &objectGraph) const
{
    return 0.0f;
}

const ObjectGraphNode* ObjectGraph::insertNewNode(int x, int y)
{
    // TODO: Check if edge exists

    ObjectGraphNode* node = new ObjectGraphNode(x, y);
    nodes.push_back(node);

    return node;
}

const ObjectGraphEdge* ObjectGraph::insertNewEdge(const ObjectGraphNode* start, const ObjectGraphNode* end)
{
    // TODO: Check if edge exists

    ObjectGraphEdge* edge = new ObjectGraphEdge(*start, *end);
    edges.push_back(edge);

    return edge;
}

int ObjectGraph::getNodeCount() const
{
    return nodes.size();
}

int ObjectGraph::getEdgeCount() const
{
    return edges.size();
}

const ObjectGraphNode *ObjectGraph::findNode(cv::Point2i coordinates)
{
    ObjectGraphNode tmpNode(coordinates.x, coordinates.y);
    auto iterator = nodes.find(&tmpNode);

    if(iterator == nodes.end())
        return 0;
    return *iterator;
}

const ObjectGraphEdge *ObjectGraph::findEdge(cv::Point2i start, cv::Point2i end)
{
    for(auto edge : edges)
    {
        if( (edge->getStart() == start && edge->getEnd() == end)
           || (edge->getStart() == end && edge->getEnd() == start) )
        {
            return edge;
        }
    }
    return 0;
}
