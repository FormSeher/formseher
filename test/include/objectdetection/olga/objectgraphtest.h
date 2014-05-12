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
        const ObjectGraphNode* node = graph.insertNewNode(2, 3);
        const ObjectGraphNode* node2 = graph.insertNewNode(1, 1);

        QVERIFY(2 == graph.getNodeCount());

        QVERIFY(node->x == 2);
        QVERIFY(node->y == 3);

        QVERIFY(node2->x == 1);
        QVERIFY(node2->y == 1);
    }

    void insertNewEdgeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* start = graph.insertNewNode(1, 1);
        const ObjectGraphNode* end = graph.insertNewNode(1, 5);

        const ObjectGraphEdge* edge = graph.insertNewEdge(start, end);

        QVERIFY(*start == edge->getStart());
        QVERIFY(*end == edge->getEnd());

        QVERIFY(1 == graph.getEdgeCount());
        QVERIFY(4 == edge->getDistance());
    }

    void findNodeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* node = graph.insertNewNode(1, 1);

        QVERIFY(node == graph.findNode(cv::Point(1, 1)));
        QVERIFY(0 == graph.findNode(cv::Point(1, 0)));
    }

    void findEdgeTest()
    {
        ObjectGraph graph;

        const ObjectGraphNode* start = graph.insertNewNode(1, 1);
        const ObjectGraphNode* end = graph.insertNewNode(1, 5);

        const ObjectGraphEdge* edge = graph.insertNewEdge(start, end);

        const ObjectGraphEdge* foundEdge = graph.findEdge(*start, *end);
        QVERIFY(edge == foundEdge);

        foundEdge = graph.findEdge(*end, *start);
        QVERIFY(edge == foundEdge);

        QVERIFY(0 == graph.findEdge(cv::Point(0, 200), *start));
    }
};

#endif // OBJECTGRAPHTEST_H
