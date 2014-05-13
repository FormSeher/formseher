#ifndef OBJECTGRAPHNODETEST_H
#define OBJECTGRAPHNODETEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/olga/objectgraphnode.h"
#include "objectdetection/olga/objectgraphedge.h"

class ObjectGraphNodeTest : public QObject
{
Q_OBJECT

private slots:
    void testAddAndGetEdge()
    {
        ObjectGraphNode node1(1, 1);
        ObjectGraphNode node2(2, 2);

        ObjectGraphEdge edge(node1, node2);

        node1.addEdge(&edge);

        QVERIFY(1 == node1.getEdges().size());
        QVERIFY(edge == *node1.getEdges().front());
    }
};

#endif // OBJECTGRAPHNODETEST_H
