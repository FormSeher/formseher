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
        ObjectGraphNode node1;
        node1.x = 0;
        node1.y = 1;

        ObjectGraphNode node2;
        node2.x = 10;
        node2.y = 1;

        ObjectGraphEdge edge(node1, node2);

        QVERIFY(10 == edge.getDistance());
        QVERIFY(cv::Vec2i(1, 0) == edge);
    }
};

#endif // OBJECTGRAPHEDGETEST_H
