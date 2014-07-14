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

#ifndef POINTERCOMPARETEST_H
#define POINTERCOMPARETEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "pointercompare.h"

using namespace formseher;

class PointerCompareTest : public QObject
{
Q_OBJECT

private slots:
    void compareTest()
    {
        PointerCompare<int> cmp;

        int x = 0;
        int y = 1;

        QVERIFY(cmp(&x, &y));
        QVERIFY(!cmp(&y, &x));
    }
};

#endif // POINTERCOMPARETEST_H
