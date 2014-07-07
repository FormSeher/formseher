#ifndef FS_OBJECTGRAPHNODE_H
#define FS_OBJECTGRAPHNODE_H

#include <opencv2/core/core.hpp>
#include <vector>

namespace formseher
{

//#include "objectdetection/olga/objectgraphedge.h"
class ObjectGraphEdge;

class ObjectGraphNode
{
public:
    /**
     * @brief ObjectGraphNode constructor.
     * @param x x-coordinate of node.
     * @param y y-coordinate of node.
     */
    ObjectGraphNode(int x, int y);

    /**
     * @brief Add a new edge to the node.
     * @param edge The edge added to the node.
     */
    void addEdge(const ObjectGraphEdge* edge);

    /**
     * @brief Get all edges connected to the node.
     * @return Vector of edges.
     */
    const std::vector<const ObjectGraphEdge*>& getEdges() const;

    /**
     * @brief Equals operator for nodes.
     * @param rhs Right hand side operand.
     * @return True if the nodes are equal.
     */
    bool operator==(const ObjectGraphNode& rhs) const;

    /**
     * @brief Less operator for nodes.
     * @param rhs Right hand side operand.
     * @return True if this node is less than rhs node.
     */
    bool operator<(const ObjectGraphNode& rhs) const;

    /**
     * @brief Get the coordinates of the node.
     * @return The coordinates.
     */
    cv::Point2i getCoordinates() const;

private:
    std::vector<const ObjectGraphEdge*> edges;

    cv::Point2i coordinates;
};

} // namespace formseher

#endif // FS_OBJECTGRAPHNODE_H
