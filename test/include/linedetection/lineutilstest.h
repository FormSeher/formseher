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

#ifndef LINEUTILSTEST_H
#define LINEUTILSTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <iostream>

// brute force private to public (don't do this at home kids!)
#undef private
#define private public

#include "linedetection/lineutils.h"

// Restore visibilities
#undef private
#define private private

using namespace formseher;

class LineUtilsTest : public QObject
{
Q_OBJECT

private slots:
    void combineLinesTest()
    {
        LineUtils lu;
        std::vector<Line> linevec;
        Line line1(20,20,20,60);
        Line line2(20,60,20,100);
        Line line3(0,0,10,10);
        Line line4(20,108,20,180);
        Line line5(40,40,100,1);

        linevec.push_back(line1);
        linevec.push_back(line2);
        linevec.push_back(line3);
        linevec.push_back(line4);
        linevec.push_back(line5);

        lu.combineLines(linevec);

        Line result = linevec.at(0);

        cv::Point2i start = result.getStart();
        cv::Point2i end = result.getEnd();

        cv::Point2i newStart(20,20);
        cv::Point2i newEnd(20,180);

        QCOMPARE(start,newStart);
        QCOMPARE(end,newEnd);
    }
};
#endif // LINEUTILSTEST_H
