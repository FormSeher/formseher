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

#include <QtTest>

#include <iostream>

#include "linetest.h"
#include "pointercomparetest.h"

#include "linedetection/edl/edltest.h"
#include "linedetection/edl2/edl2test.h"

#include "linedetection/lineutilstest.h"

#include "objectdetection/olga/objectgraphedgetest.h"
#include "objectdetection/olga/objectgraphnodetest.h"
#include "objectdetection/olga/objectgraphtest.h"

#include "objectdetection/modeltest.h"
#include "objectdetection/objecttest.h"

#include "objectdetection/haff/haffdatabasetest.h"
#include "objectdetection/haff/hypothesistest.h"
#include "objectdetection/haff/hafftest.h"

#include "objectdetection/databaseutilstest.h"

#include "objectdetection/teamb/objectdetectionteambtest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    PointerCompareTest pointerCompareTest;

    LineUtilsTest lineUtilsTest;

    EDLTest edlTest;
    EDL2Test edl2Test;

    ObjectGraphEdgeTest objectGraphEdgeTest;
    ObjectGraphNodeTest objectGraphNodeTest;
    ObjectGraphTest objectGraphTest;

    ModelTest modelTest;
    ObjectTest objectTest;

    HaffDatabaseTest haffDatabaseTest;
    HypothesisTest hypothesisTest;
    HaffTest haffTest;

    DatabaseUtilsTest databaseUtilsTest;

    ObjectDetectionTeamBTest objectDetectionTeamBTest;

    bool testsFailed =
             QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&pointerCompareTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv)
           | QTest::qExec(&edl2Test, argc, argv)
           | QTest::qExec(&objectGraphEdgeTest, argc, argv)
           | QTest::qExec(&objectGraphTest, argc, argv)
           | QTest::qExec(&objectGraphNodeTest, argc, argv)
           | QTest::qExec(&objectTest, argc, argv)
           | QTest::qExec(&haffDatabaseTest, argc, argv)
           | QTest::qExec(&hypothesisTest, argc, argv)
           | QTest::qExec(&haffTest, argc, argv)
           | QTest::qExec(&modelTest, argc, argv)
           | QTest::qExec(&objectTest, argc, argv)
           | QTest::qExec(&databaseUtilsTest, argc, argv)
           | QTest::qExec(&objectDetectionTeamBTest, argc, argv)
           | QTest::qExec(&lineUtilsTest, argc, argv);

    if(testsFailed)
        std::cerr << "Some tests failed. Fix them! ò.Ó" << std::endl;
    else
        std::cout << "All tests successful." << std::endl;

    return testsFailed;
}
