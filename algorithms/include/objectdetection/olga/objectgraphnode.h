/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

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
