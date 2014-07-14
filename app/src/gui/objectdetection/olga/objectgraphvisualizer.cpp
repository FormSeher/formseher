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

#include "gui/objectdetection/olga/objectgraphvisualizer.h"

#include "objectdetection/olga/objectgraph.h"

namespace formseher
{

ObjectGraphVisualizer::ObjectGraphVisualizer()
{
}

void ObjectGraphVisualizer::drawGraphOnMatrix(const ObjectGraph* graph, cv::OutputArray _matrix)
{
    int borderWidth = 10;
    cv::Scalar nodeColor(12, 127, 232);
    cv::Scalar edgeColor(0, 240, 255);

    cv::Rect graphBox = graph->getBoundingBox();
    // tl = top left corner of bounding box
    cv::Point tl = graphBox.tl() - cv::Point(borderWidth, borderWidth);

    _matrix.create(graphBox.size() + cv::Size(2 * borderWidth, 2 * borderWidth), CV_8UC3);
    cv::Mat matrix = _matrix.getMat();

    // Draw edges
    for(auto edge : graph->getEdges())
        cv::line(matrix, edge->getStart().getCoordinates() - tl, edge->getEnd().getCoordinates() - tl, edgeColor, 1);

    // Draw nodes
    for(auto node : graph->getNodes())
        cv::circle(matrix, node->getCoordinates() - tl, 3, nodeColor, -1);
}

} // namespace formseher
