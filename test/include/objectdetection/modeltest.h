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

#ifndef FS_MODELTEST_H
#define FS_MODELTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include <opencv2/core/core.hpp>

#include "objectdetection/model.h"
#include "line.h"

using namespace formseher;

class ModelTest : public QObject
{
Q_OBJECT

private slots:
    void copyConstructorTest()
    {
        Model m1;
        m1.setName("m1");
        m1.addLine(Line(1, 1, 2, 2));

        Model m2(m1);

        QVERIFY(m1.getName() == m2.getName());
        QVERIFY(m1.getBoundingBox() == m2.getBoundingBox());

        QVERIFY(m1.getLines().size() == m2.getLines().size());

        const Line* l1 = m1.getLines().at(0);
        const Line* l2 = m2.getLines().at(0);

        // Check if pointers are different
        QVERIFY(l1 != l2);
        // Check if line objects are equal
        QVERIFY(l1->getStart() == l2->getStart());
        QVERIFY(l1->getEnd() == l2->getEnd());
    }

    void assignmentOperatorTest()
    {
        Model m1;
        m1.setName("m1");
        m1.addLine(Line(1, 1, 2, 2));

        Model m2;
        m2.setName("m2");
        m2.addLine(Line(50, 60, 70, 80));
        m2 = m1;

        QVERIFY(m1.getName() == m2.getName());
        QVERIFY(m1.getBoundingBox() == m2.getBoundingBox());

        QVERIFY(m1.getLines().size() == m2.getLines().size());

        const Line* l1 = m1.getLines().at(0);
        const Line* l2 = m2.getLines().at(0);

        // Check if pointers are different
        QVERIFY(l1 != l2);
        // Check if line objects are equal
        QVERIFY(l1->getStart() == l2->getStart());
        QVERIFY(l1->getEnd() == l2->getEnd());
    }

    void nameTest()
    {
        Model m;
        m.setName("This is object!");
        QVERIFY("This is object!" == m.getName());
    }

    void addLineTest()
    {
        Model m;
        Line line1(1, 2, 3, 4);
        Line line2(5, 6, 7, 9);

        m.addLine(line1);
        m.addLine(line2);

        QVERIFY(2 == m.getLines().size());
        QVERIFY(cv::Point2i(1, 2) == m.getLines().at(0)->getStart());
        QVERIFY(cv::Point2i(7, 9) == m.getLines().at(1)->getEnd());

        QVERIFY(cv::Rect(1, 2, 6, 7) == m.getBoundingBox());
    }

    void toStringTest()
    {
        Model m;
        m.setName("Fancy object");
        m.addLine(Line(10, 2, 3, 4));
        m.addLine(Line(5, 666, 7, 8));

        std::string serialized = m.toString();

        QVERIFY("Fancy object:10,2,3,4;5,666,7,8;" == serialized);
    }

    void fromStringTest()
    {
        std::string serialized = "Fancy object:10,2,3,4;5,666,7,8;";

        Model m;
        m.fromString(serialized);

        QVERIFY("Fancy object" == m.getName());
        QVERIFY(2 == m.getLines().size());

        auto lines = m.getLines();
        QVERIFY(cv::Point2i(10, 2) == lines.at(0)->getStart());
        QVERIFY(cv::Point2i( 3, 4) == lines.at(0)->getEnd());
        QVERIFY(cv::Point2i( 5, 666) == lines.at(1)->getStart());
        QVERIFY(cv::Point2i( 7, 8) == lines.at(1)->getEnd());
    }
};

#endif // FS_MODELTEST_H
