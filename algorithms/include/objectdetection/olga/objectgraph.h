#ifndef OBJECTGRAPH_H
#define OBJECTGRAPH_H

#include <vector>
#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphedge.h"
#include "objectdetection/olga/objectgraphnode.h"

class ObjectGraph
{
public:
    ObjectGraph();

    /**
     * @brief Compares this ObjectGraph to another ObjectGraph.
     * @param The ObjectGraph compared against.
     * @return An approximation of how equal the two ObjectGraphs are. Lies between
     * 0.0 (0%) if they are disjunct or 1.0 (100%) if they are equal.
     */
    float compareTo(const ObjectGraph& objectGraph) const;

private:
    std::vector<ObjectGraphNode> nodes;
    std::vector<ObjectGraphEdge> edges;
};

#endif // OBJECTGRAPH_H
