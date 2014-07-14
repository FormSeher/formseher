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

#include "objectdetection/olga/objectgraphnode.h"

namespace formseher
{

ObjectGraphNode::ObjectGraphNode(int x, int y)
    : coordinates(x, y)
{
}

void ObjectGraphNode::addEdge(const ObjectGraphEdge* edge)
{
    edges.push_back(edge);
}

const std::vector<const ObjectGraphEdge*> &ObjectGraphNode::getEdges() const
{
    return edges;
}

bool ObjectGraphNode::operator==(const ObjectGraphNode &rhs) const
{
    return this->getCoordinates() == rhs.getCoordinates();
}

bool ObjectGraphNode::operator<(const ObjectGraphNode &rhs) const
{
    return this->getCoordinates().y < rhs.getCoordinates().y
            || this->getCoordinates().x < rhs.getCoordinates().x;
}

cv::Point2i ObjectGraphNode::getCoordinates() const
{
    return coordinates;
}

}
