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

#ifndef FS_HAFFTEST_H
#define FS_HAFFTEST_H

#include <QtTest>
#include <QObject>

// brute force private to public (don't do this at home kids!)
#undef private
#define private public

#include "objectdetection/haff/haff.h"

// Restore visibilities
#undef private
#define private private

#include "line.h"
#include "objectdetection/object.h"

using namespace formseher;

class HaffTest : public QObject
{
Q_OBJECT

private slots:
    void calcualateTest()
    {
        Haff haff;

        std::vector<Line> detectedLines;
        detectedLines.push_back(Line(0, 0, 1, 0));
        detectedLines.push_back(Line(1, 0, 1, 1));
        detectedLines.push_back(Line(1, 1, 0, 1));
        detectedLines.push_back(Line(0, 1, 0, 0));

        std::vector<Model> databaseModels;

        Model model;
        model.setName("model");
        model.addLine(Line(0, 0, 1, 0));
        model.addLine(Line(1, 0, 1, 1));
        model.addLine(Line(1, 1, 0, 1));
        model.addLine(Line(0, 1, 0, 0));

        databaseModels.push_back(model);

        haff.setModels(databaseModels);

        std::vector<Object> objects = haff.calculate(detectedLines);

        QCOMPARE(objects.size(), (size_t)1);
    }

    void symetricReplacementTest()
    {
        Haff haff;

        std::vector<Object> objects;

        Object object1;
        object1.setName("Object 1");
        object1.addLine(Line(0, 0, 100, 100));
        object1.setRating(0.6);

        Object object2;
        object2.setName("Object 2");
        object2.addLine(Line(25, 25, 75, 75));
        object2.setRating(0.7);

        Object object3;
        object3.setName("Object 3");
        object3.addLine(Line(40, 40, 90, 90));
        object3.setRating(0.6);

        objects.push_back(object1);

        QCOMPARE(objects.size(), (size_t)1);

        haff.suppressedInsertion(objects, object1);

        QCOMPARE(objects.size(), (size_t) 1);
        QCOMPARE(objects.at(0).getName(), (std::string)"Object 1");

        haff.suppressedInsertion(objects, object2);
        QCOMPARE(objects.size(), (size_t) 1);
        QCOMPARE(objects.at(0).getName(), (std::string)"Object 2");

        haff.suppressedInsertion(objects, object1);
        QCOMPARE(objects.size(), (size_t) 1);
        QCOMPARE(objects.at(0).getName(), (std::string)"Object 2");

        haff.suppressedInsertion(objects, object3);
        QCOMPARE(objects.size(), (size_t) 1);
        QCOMPARE(objects.at(0).getName(), (std::string)"Object 2");
    }


};

#endif // FS_HAFFTEST_H
