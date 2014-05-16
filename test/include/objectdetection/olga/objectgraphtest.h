#ifndef OBJECTGRAPHTEST_H
#define OBJECTGRAPHTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/olga/objectgraph.h"

class ObjectGraphTest : public QObject
{
Q_OBJECT

private slots:
    void insertNewNodeTest()
    {
        ObjectGraph graph;
        const ObjectGraphNode* node = graph.insertNode(2, 3);
        const ObjectGraphNode* node1 = graph.insertNode(2, 3);
        const ObjectGraphNode* node2 = graph.insertNode(1, 1);

        QVERIFY(2 == graph.getNodeCount());

        QVERIFY(node->x == 2);
        QVERIFY(node->y == 3);

        QVERIFY(node == node1);

        QVERIFY(node2->x == 1);
        QVERIFY(node2->y == 1);
    }

    void insertNewEdgeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* start = graph.insertNode(1, 1);
        const ObjectGraphNode* end = graph.insertNode(1, 5);

        const ObjectGraphEdge* edge = graph.insertEdge(start, end);

        QVERIFY(*start == edge->getStart());
        QVERIFY(*end == edge->getEnd());

        QVERIFY(1 == graph.getEdgeCount());
        QVERIFY(4 == edge->getDistance());

        // Check if edges have been added to nodes
        QVERIFY(start->getEdges().size() == 1);
        QVERIFY(end->getEdges().size() == 1);

        QVERIFY(edge == start->getEdges().at(0));
        QVERIFY(edge == end->getEdges().at(0));
    }

    void findNodeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* node = graph.insertNode(1, 1);

        QVERIFY(node == graph.findNode(cv::Point(1, 1)));
        QVERIFY(0 == graph.findNode(cv::Point(1, 0)));
    }

    void findEdgeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* start = graph.insertNode(1, 1);
        const ObjectGraphNode* end = graph.insertNode(1, 5);

        const ObjectGraphEdge* edge = graph.insertEdge(start, end);

        const ObjectGraphEdge* foundEdge = graph.findEdge(*start, *end);
        QVERIFY(edge == foundEdge);

        foundEdge = graph.findEdge(*end, *start);
        QVERIFY(edge == foundEdge);

        QVERIFY(0 == graph.findEdge(cv::Point(0, 200), *start));
    }
};

#endif // OBJECTGRAPHTEST_H
