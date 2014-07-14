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

#ifndef FS_OBJECTGRAPHNODETEST_H
#define FS_OBJECTGRAPHNODETEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/olga/objectgraphnode.h"
#include "objectdetection/olga/objectgraphedge.h"

using namespace formseher;

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

    void testOperatorEquals()
    {
        ObjectGraphNode node1(1, 1);
        ObjectGraphNode node2(1, 1);
        ObjectGraphNode node3(1, 0);

        QVERIFY(node1 == node2);
        QVERIFY(node2 == node1);
        QVERIFY(!(node1 == node3));
        QVERIFY(!(node3 == node2));
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

#endif // FS_OBJECTGRAPHNODETEST_H
