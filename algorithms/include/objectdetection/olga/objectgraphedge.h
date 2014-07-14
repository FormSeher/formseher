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

#ifndef FS_OBJECTGRAPHEDGE_H
#define FS_OBJECTGRAPHEDGE_H

#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphnode.h"

namespace formseher
{

/**
 * @brief The ObjectGraphEdge class used by ObjectGraph.
 *
 * ObjectGraphEdges are unweighted, undirected edges. End node and start node are only names to distinguish between the nodes.
 */
class ObjectGraphEdge
{
public:
    /**
     * @brief Create edge between given nodes.
     * @param start Start node of edge.
     * @param end End node of edge.
     */
    ObjectGraphEdge(ObjectGraphNode& start, ObjectGraphNode& end);

    /**
     * @brief Length of the edge.
     * @return Returns length (distnace of start to end node) of the edge.
     */
    int getDistance() const;

    /**
     * @brief Equals operator to compare ObjectGraphEdges.
     * @param rhs Right hand side operand.
     * @return True if edges are equal.
     */
    bool operator==(const ObjectGraphEdge& rhs);

    /**
     * @brief Not-equals operator to compare ObjectGraphEdges.
     * @param rhs Right hand side operand.
     * @return False if edges are equal.
     */
    bool operator!=(const ObjectGraphEdge& rhs);

    /**
     * @brief Get start of the edge.
     * @return The start node.
     */
    ObjectGraphNode& getStart() const;

    /**
     * @brief Get end of the edge.
     * @return The end node.
     */
    ObjectGraphNode& getEnd() const;

    /**
     * @brief Converts the edge to a OpenCV vector.
     * @return Vector representation of the edge.
     */
    cv::Vec2i toCvVector() const;

private:
    cv::Vec2i vector;

    int distance;

    ObjectGraphNode& start;
    ObjectGraphNode& end;
};

} // namespace formseher

#endif // FS_OBJECTGRAPHEDGE_H
