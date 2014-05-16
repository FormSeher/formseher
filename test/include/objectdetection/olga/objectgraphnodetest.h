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

    void testOperatorLess()
    {
        ObjectGraphNode node11(1, 0);
        ObjectGraphNode node11_2(1, 0);
        ObjectGraphNode node20(2, 0);

        QVERIFY(node11 < node20);
        QVERIFY(!(node20 < node20));

        // Check equality
        QVERIFY(! (node11 < node11_2));
        QVERIFY(! (node11_2 < node11));
    }
};

#endif // OBJECTGRAPHNODETEST_H
