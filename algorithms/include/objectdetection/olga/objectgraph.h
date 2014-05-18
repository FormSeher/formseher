#ifndef FS_OBJECTGRAPH_H
#define FS_OBJECTGRAPH_H

#include <vector>
#include <map>
#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphedge.h"
#include "objectdetection/olga/objectgraphnode.h"
#include "pointercompare.h"

namespace formseher
{

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
    const ObjectGraphNode* insertNode(int x, int y);

    /**
     * @brief Insert a new edge between two nodes.
     * @param start The start of the edge.
     * @param end The end of the edge.
     * @return Pointer to the newly created edge.
     */
    const ObjectGraphEdge* insertEdge(const ObjectGraphNode* start, const ObjectGraphNode* end);

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
     * @brief Find a node in the graph.
     * @param coordinates The coordinates of the searched node.
     * @return Pointer to the node or null if no node was found.
     */
    const ObjectGraphNode* findNode(cv::Point2i coordinates);

    /**
     * @brief Find an edge in the graph.
     * @param start One end of the edge.
     * @param end The other end of the edge.
     * @return Pointer to the edge or null if no edge was found.
     */
    const ObjectGraphEdge* findEdge(cv::Point2i start, cv::Point2i end);

private:
    std::map<const ObjectGraphNode*, ObjectGraphNode*, PointerCompare<ObjectGraphNode>> nodes;
    std::vector<ObjectGraphEdge*> edges;
};

} // namespace formseher

#endif // FS_OBJECTGRAPH_H
