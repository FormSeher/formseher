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

#include "objectdetection/olga/objectgraphedge.h"

namespace formseher
{

ObjectGraphEdge::ObjectGraphEdge(ObjectGraphNode& start, ObjectGraphNode& end)
    : vector(end.getCoordinates() - start.getCoordinates()),
      start(start),
      end(end)
{
    distance = cv::norm(vector);
    cv::normalize(vector, vector);
}

int ObjectGraphEdge::getDistance() const
{
    return distance;
}

bool ObjectGraphEdge::operator==(const ObjectGraphEdge &rhs)
{
    if(vector != rhs.toCvVector())
        return false;
    if(this->getDistance() != rhs.getDistance())
        return false;
    return true;
}

bool ObjectGraphEdge::operator!=(const ObjectGraphEdge &rhs)
{
    return !((*this) == rhs);
}

ObjectGraphNode& ObjectGraphEdge::getStart() const
{
    return start;
}

ObjectGraphNode& ObjectGraphEdge::getEnd() const
{
    return end;
}

cv::Vec2i ObjectGraphEdge::toCvVector() const
{
    return vector;
}

}
