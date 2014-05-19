#ifndef FS_OBJECTGRAPHTEST_H
#define FS_OBJECTGRAPHTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/olga/objectgraph.h"

using namespace formseher;

class ObjectGraphTest : public QObject
{
Q_OBJECT

private slots:
    void insertNewNodeTest()
    {
        ObjectGraph graph;
        ObjectGraphNode* node = graph.insertNode(2, 3);
        ObjectGraphNode* node1 = graph.insertNode(2, 3);
        ObjectGraphNode* node2 = graph.insertNode(1, 1);

        QVERIFY(2 == graph.getNodeCount());
        QVERIFY(2 == graph.getNodes().size());

        QVERIFY(node->getCoordinates() == cv::Point2i(2, 3));
        QVERIFY(node == node1);
        QVERIFY(node2->getCoordinates() == cv::Point2i(1, 1));

    }

    void insertNewEdgeTest()
    {
        ObjectGraph graph;

        ObjectGraphNode* start = graph.insertNode(1, 1);
        ObjectGraphNode* end = graph.insertNode(1, 5);

        ObjectGraphEdge* edge1 = graph.insertEdge(start, end);
        // Insert same edge with swapped start/end points
        ObjectGraphEdge* edge2 = graph.insertEdge(end, start);

        QVERIFY(*start == edge1->getStart());
        QVERIFY(*end == edge1->getEnd());

        QVERIFY(edge1 == edge2);

        QVERIFY(1 == graph.getEdgeCount());
        QVERIFY(1 == graph.getEdges().size());

        // Check if edges have been added to nodes
        QVERIFY(start->getEdges().size() == 1);
        QVERIFY(end->getEdges().size() == 1);

        QVERIFY(4 == edge1->getDistance());
        QVERIFY(edge1 == start->getEdges().at(0));
        QVERIFY(edge1 == end->getEdges().at(0));
    }

    void findNodeTest()
    {
        ObjectGraph graph;

        ObjectGraphNode* node = graph.insertNode(1, 1);

        QVERIFY(node == graph.findNode(cv::Point(1, 1)));
        QVERIFY(0 == graph.findNode(cv::Point(1, 0)));
    }

    void findEdgeTest()
    {
        ObjectGraph graph;

        ObjectGraphNode* start = graph.insertNode(1, 1);
        ObjectGraphNode* end = graph.insertNode(1, 5);

        ObjectGraphEdge* edge = graph.insertEdge(start, end);

        ObjectGraphEdge* foundEdge = graph.findEdge(start, end);
        QVERIFY(edge == foundEdge);

        foundEdge = graph.findEdge(end, start);
        QVERIFY(edge == foundEdge);
    }

    void boundingBoxTest()
    {
        ObjectGraph graph;

        graph.insertNode(1, 1);
        QVERIFY(cv::Rect(1, 1, 0, 0) == graph.getBoundingBox());

        graph.insertNode(2, 3);
        QVERIFY(cv::Rect(1, 1, 1, 2) == graph.getBoundingBox());

        graph.insertNode(3, 0);
        QVERIFY(cv::Rect(1, 0, 2, 3) == graph.getBoundingBox());

        graph.insertNode(2, 2);
        QVERIFY(cv::Rect(1, 0, 2, 3) == graph.getBoundingBox());

        graph.insertNode(0, 4);
        QVERIFY(cv::Rect(0, 0, 3, 4) == graph.getBoundingBox());
    }
};

#endif // FS_OBJECTGRAPHTEST_H
