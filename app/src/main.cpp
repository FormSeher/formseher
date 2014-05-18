#include <gui/mainwindow.h>
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "gui/algorithmconfigdialog.h"
#include "gui/edl/edlconfigdialog.h"
#include "gui/hough/houghconfigdialog.h"

#include "objectdetection/olga/objectgraph.h"
#include "gui/objectdetection/olga/objectgraphvisualizer.h"

int main(int argc, char *argv[])
{
    formseher::ObjectGraph objectGraph;
    formseher::ObjectGraphNode* node1 = objectGraph.insertNode(10, 100);
    formseher::ObjectGraphNode* node2 = objectGraph.insertNode(300, 50);
    formseher::ObjectGraphNode* node3 = objectGraph.insertNode(30, 150);
    formseher::ObjectGraphNode* node4 = objectGraph.insertNode(50, 100);
    objectGraph.insertEdge(node1, node2);
    objectGraph.insertEdge(node2, node3);
    objectGraph.insertEdge(node1, node3);
    objectGraph.insertEdge(node4, node3);

    cv::Mat graphMatrix;
    formseher::ObjectGraphVisualizer::drawGraphOnMatrix(&objectGraph, graphMatrix);
    cv::imshow("object graph", graphMatrix);
    cv::waitKey(0);

//    QApplication a(argc, argv);

//    formseher::EDLConfigDialog edlDialog1;
//    formseher::EDLConfigDialog edlDialog2;

//    formseher::HoughConfigDialog houghDialog1;
//    formseher::HoughConfigDialog houghDialog2;

//    formseher::MainWindow w;


//    w.registerAlgorithmConfigDialog(1, "EDL", static_cast<formseher::AlgorithmConfigDialog*>(&edlDialog1));
//    w.registerAlgorithmConfigDialog(2, "EDL", static_cast<formseher::AlgorithmConfigDialog*>(&edlDialog2));
//    w.registerAlgorithmConfigDialog(1, "Hough", static_cast<formseher::AlgorithmConfigDialog*>(&houghDialog1));
//    w.registerAlgorithmConfigDialog(2, "Hough", static_cast<formseher::AlgorithmConfigDialog*>(&houghDialog2));

//    w.show();

//    return a.exec();
}
