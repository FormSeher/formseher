#include <QtTest>

#include <iostream>

#include "linetest.h"
#include "pointercomparetest.h"

#include "linedetection/edl/edltest.h"
#include "linedetection/edl2/edl2test.h"

#include "objectdetection/olga/objectgraphedgetest.h"
#include "objectdetection/olga/objectgraphnodetest.h"
#include "objectdetection/olga/objectgraphtest.h"

#include "objectdetection/modeltest.h"
#include "objectdetection/objecttest.h"

#include "objectdetection/haff/haffdatabasetest.h"
#include "objectdetection/haff/hypothesistest.h"

#include "objectdetection/databaseutilstest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    PointerCompareTest pointerCompareTest;

    EDLTest edlTest;
    EDL2Test edl2Test;

    ObjectGraphEdgeTest objectGraphEdgeTest;
    ObjectGraphNodeTest objectGraphNodeTest;
    ObjectGraphTest objectGraphTest;

    ModelTest modelTest;
    ObjectTest objectTest;

    HaffDatabaseTest haffDatabaseTest;
    HypothesisTest hypothesisTest;

    DatabaseUtilsTest databaseUtilsTest;

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
           | QTest::qExec(&modelTest, argc, argv)
           | QTest::qExec(&objectTest, argc, argv)
           | QTest::qExec(&databaseUtilsTest, argc, argv);

    if(testsFailed)
        std::cerr << "Some tests failed. Fix them! ò.Ó" << std::endl;
    else
        std::cout << "All tests successful." << std::endl;

    return testsFailed;
}
