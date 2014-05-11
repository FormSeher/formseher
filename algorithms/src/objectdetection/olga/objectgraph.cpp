#include "objectdetection/olga/objectgraph.h"

ObjectGraph::ObjectGraph()
{
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

int ObjectGraph::getNodeCount() const
{
    return nodes.size();
}
