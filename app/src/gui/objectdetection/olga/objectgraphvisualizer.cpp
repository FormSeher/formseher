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
