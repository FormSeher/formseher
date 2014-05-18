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

float ObjectGraph::compareTo(const ObjectGraph &objectGraph) const
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

ObjectGraphEdge* ObjectGraph::insertEdge(ObjectGraphNode* start, ObjectGraphNode* end)
{
    // TODO: Check if edge exists

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

ObjectGraphNode *ObjectGraph::findNode(cv::Point2i coordinates)
{
    ObjectGraphNode tmpNode(coordinates.x, coordinates.y);
    auto iterator = nodes.find(&tmpNode);

    if(iterator == nodes.end())
        return 0;
    return *iterator;
}

ObjectGraphEdge *ObjectGraph::findEdge(cv::Point2i start, cv::Point2i end)
{
    for(auto edge : edges)
    {
        if( (edge->getStart().getCoordinates() == start && edge->getEnd().getCoordinates() == end)
           || (edge->getStart().getCoordinates() == end && edge->getEnd().getCoordinates() == start) )
        {
            return edge;
        }
    }
    return 0;
}

ObjectGraphEdge *ObjectGraph::findEdge(const ObjectGraphNode &start, const ObjectGraphNode &end)
{
    return findEdge(start.getCoordinates(), end.getCoordinates());
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
