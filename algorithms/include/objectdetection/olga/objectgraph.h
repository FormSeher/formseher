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
    ~ObjectGraph();

    /**
     * @brief Compares this ObjectGraph to another ObjectGraph.
     * @param The ObjectGraph compared against.
     * @return An approximation of how equal the two ObjectGraphs are. Lies between
     * 0.0 (0%) if they are disjunct or 1.0 (100%) if they are equal.
     */
    float compareTo(const ObjectGraph& objectGraph) const;

    /**
     * @brief Insert a new node with given parameters.
     * @param x The x-coordinate of the node.
     * @param y The y-coordinate of the node.
     * @return Pointer to the newly created node.
     */
    const ObjectGraphNode* insertNewNode(int x, int y);

    /**
     * @brief Insert a new edge between two nodes.
     * @param start The start of the edge.
     * @param end The end of the edge.
     * @return Pointer to the newly created edge.
     */
    const ObjectGraphEdge* insertNewEdge(const ObjectGraphNode* start, const ObjectGraphNode* end);

    /**
     * @brief Get the number of nodes added to the graph.
     * @return Number of nodes.
     */
    int getNodeCount() const;

    /**
     * @brief Get the number of edges added to the graph.
     * @return Number of edges.
     */
    int getEdgeCount() const;

    /**
     * @brief Find an edge in the graph.
     * @param start One end of the edge.
     * @param end The other end of the edge.
     * @return Pointer to the edge or null if no edge was found.
     */
    const ObjectGraphEdge* findEdge(cv::Point2i start, cv::Point2i end);

private:
    std::vector<ObjectGraphNode*> nodes;
    std::vector<ObjectGraphEdge*> edges;
};

#endif // OBJECTGRAPH_H
