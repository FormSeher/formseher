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

#ifndef FS_OBJECTTEST_H
#define FS_OBJECTTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/object.h"

using namespace formseher;

class ObjectTest : public QObject
{
Q_OBJECT

private slots:
    void copyConstructorTest()
    {
        Object o1;
        o1.setName("m1");
        o1.addLine(Line(1, 1, 2, 2));
        o1.setRating(22.13);

        Object o2(o1);

        // Check if parent copy constructor was called
        QVERIFY(o1.getLines().at(0) != o2.getLines().at(0));

        QVERIFY(o1.getRating() == o2.getRating());
    }

    void ratingTest()
    {
        Object o;
        o.setRating(12.25);
        QVERIFY(12.25f == o.getRating());
    }
};

#endif // FS_OBJECTTEST_H
