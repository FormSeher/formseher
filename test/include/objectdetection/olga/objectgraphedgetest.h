#ifndef OBJECTGRAPHEDGETEST_H
#define OBJECTGRAPHEDGETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>

#include "objectdetection/olga/objectgraphnode.h"
#include "objectdetection/olga/objectgraphedge.h"

class ObjectGraphEdgeTest : public QObject
{
Q_OBJECT

private slots:
    void constructorTest()
    {
        ObjectGraphNode node1(0, 1);
        ObjectGraphNode node2(10 ,1);

        ObjectGraphEdge edge(node1, node2);

        QVERIFY(10 == edge.getDistance());
        QVERIFY(cv::Vec2i(1, 0) == edge);
    }

    void operatorEqualTest()
    {
        ObjectGraphNode node1(0, 1);
        ObjectGraphNode node2(10, 1);

        ObjectGraphEdge edge1(node1, node2);
        ObjectGraphEdge edge2(node1, node2);

        QVERIFY(edge1 == edge2);
    }

    void operatorNotEqualTest()
    {
        ObjectGraphNode node1(0, 1);
        ObjectGraphNode node2(10, 1);
        ObjectGraphNode node3(100 ,1);

        ObjectGraphEdge edge1(node1, node2);
        ObjectGraphEdge edge2(node1, node3);

        QVERIFY(edge1 != edge2);
    }
};

#endif // OBJECTGRAPHEDGETEST_H
