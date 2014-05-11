#include <QtTest>

#include "linetest.h"

#include "linedetection/edl/edltest.h"

#include "objectdetection/olga/objectgraphedgetest.h"
#include "objectdetection/olga/objectgraphtest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    EDLTest edlTest;

    ObjectGraphEdgeTest objectGraphEdgeTest;
    ObjectGraphTest objectGraphTest;

    return   QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv)
           | QTest::qExec(&objectGraphEdgeTest, argc, argv)
           | QTest::qExec(&objectGraphTest, argc, argv);
}

