#include "objectdetection/olga/objectgraph.h"

namespace formseher
{

ObjectGraph::ObjectGraph()
{
}

ObjectGraph::~ObjectGraph()
{
    for(auto iterator : nodes)
        delete iterator.second;
    for(auto edge : edges)
        delete edge;
}

float ObjectGraph::compareTo(const ObjectGraph &objectGraph) const
{
    return 0.0f;
}

const ObjectGraphNode* ObjectGraph::insertNode(int x, int y)
{
    const ObjectGraphNode* foundNode = findNode(cv::Point2i(x, y));

    if(foundNode)
        return foundNode;

    ObjectGraphNode* newNode = new ObjectGraphNode(x, y);
    nodes[newNode] = newNode;
    return newNode;
}

const ObjectGraphEdge* ObjectGraph::insertEdge(const ObjectGraphNode* _start, const ObjectGraphNode* _end)
{
    // TODO: Check if edge exists
    ObjectGraphNode* start = nodes.find(_start)->second;
    ObjectGraphNode* end = nodes.find(_end)->second;

    ObjectGraphEdge* edge = new ObjectGraphEdge(*start, *end);
    edges.push_back(edge);

    start->addEdge(edge);
    end->addEdge(edge);

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
    return iterator->second;
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

}
