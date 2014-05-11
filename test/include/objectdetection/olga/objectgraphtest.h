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
};

#endif // OBJECTGRAPHTEST_H
