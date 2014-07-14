/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

#ifndef FS_OBJECTGRAPHEDGETEST_H
#define FS_OBJECTGRAPHEDGETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>

#include "objectdetection/olga/objectgraphnode.h"
#include "objectdetection/olga/objectgraphedge.h"

using namespace formseher;

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
        QVERIFY(cv::Vec2i(1, 0) == edge.toCvVector());

        QVERIFY(node1 == edge.getStart());
        QVERIFY(node2 == edge.getEnd());
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

#endif // FS_OBJECTGRAPHEDGETEST_H
