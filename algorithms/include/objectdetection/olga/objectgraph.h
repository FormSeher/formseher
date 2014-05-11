#ifndef OBJECTGRAPH_H
#define OBJECTGRAPH_H

#include <opencv2/core/core.hpp>

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
};

#endif // OBJECTGRAPH_H
