#include "objectdetection/olga/objectgraph.h"

namespace formseher
{

ObjectGraph::ObjectGraph()
{
}

ObjectGraph::~ObjectGraph()
{
    for(auto iterator : nodes)
        delete iterator;
    for(auto edge : edges)
        delete edge;
}

float ObjectGraph::compareTo(const ObjectGraph&) const
{
    return 0.0f;
}

ObjectGraphNode* ObjectGraph::insertNode(int x, int y)
{
    ObjectGraphNode* foundNode = findNode(cv::Point2i(x, y));

    if(foundNode)
        return foundNode;

    ObjectGraphNode* newNode = new ObjectGraphNode(x, y);
    nodes.insert(newNode);

    updateBoundingBox(newNode);

    return newNode;
}

ObjectGraphEdge* ObjectGraph::insertEdge(ObjectGraphNode* _start, ObjectGraphNode* _end)
{
    ObjectGraphNode* start;
    ObjectGraphNode* end;

    // Swap start/end so "smallest" point is start of the line
    if(*_start < *_end)
    {
        start = _start;
        end = _end;
    }
    else
    {
        start = _end;
        end = _start;
    }

    // Check if edge exists
    ObjectGraphEdge* edge = findEdge(start, end);

    if(edge)
        return edge;

    // No edge found? Create new one
    edge = new ObjectGraphEdge(*start, *end);
    edges.insert(edge);

    edgesMap[start][end] = edge;

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

ObjectGraphNode *ObjectGraph::findNode(cv::Point2i coordinates)
{
    ObjectGraphNode tmpNode(coordinates.x, coordinates.y);
    auto iterator = nodes.find(&tmpNode);

    if(iterator == nodes.end())
        return 0;
    return *iterator;
}

ObjectGraphEdge *ObjectGraph::findEdge(const ObjectGraphNode* _start, const ObjectGraphNode* _end) const
{
    const ObjectGraphNode* start;
    const ObjectGraphNode* end;

    // Swap coordinates for correct edgesMap access ("smaller" node is saved first)
    if(*_start < *_end)
    {
        start = _start;
        end = _end;
    }
    else
    {
        start = _end;
        end = _start;
    }

    // Access first level of edgesMap
    auto edgeMapIterator1 = edgesMap.find(start);
    if(edgeMapIterator1 == edgesMap.end())
        return 0;

    // Access second level of edgesMap
    auto edgeMapIterator2 = edgeMapIterator1->second.find(end);
    if(edgeMapIterator2 == edgeMapIterator1->second.end())
        return 0;

    // Return third level of edgesMap (the ObjectGraphEdge pointer)
    return edgeMapIterator2->second;
}

cv::Rect ObjectGraph::getBoundingBox() const
{
    return cv::Rect(
            boundingBoxCorners[0].x, // x
            boundingBoxCorners[0].y, // y
            boundingBoxCorners[1].x - boundingBoxCorners[0].x, // width
            boundingBoxCorners[1].y - boundingBoxCorners[0].y  // height
            );
}

const std::set<ObjectGraphNode*, PointerCompare<ObjectGraphNode>>& ObjectGraph::getNodes() const
{
    return nodes;
}

const std::set<ObjectGraphEdge *> &ObjectGraph::getEdges() const
{
    return edges;
}

void ObjectGraph::updateBoundingBox(const ObjectGraphNode* node)
{
    if(nodes.size() == 1)
    {
        boundingBoxCorners[0] = node->getCoordinates();
        boundingBoxCorners[1] = node->getCoordinates();
    }
    else
    {
        cv::Point2i coordinates = node->getCoordinates();
        // Update x coordinate
        if(boundingBoxCorners[0].x > coordinates.x)
            boundingBoxCorners[0].x = coordinates.x;
        else if(boundingBoxCorners[1].x < coordinates.x)
            boundingBoxCorners[1].x = coordinates.x;

        // Update y coordinate
        if(boundingBoxCorners[0].y > coordinates.y)
            boundingBoxCorners[0].y = coordinates.y;
        else if(boundingBoxCorners[1].y < coordinates.y)
            boundingBoxCorners[1].y = coordinates.y;
    }
}

}
