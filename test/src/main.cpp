#include <QtTest>

#include "linetest.h"
#include "edl/edltest.h"
#include "objectdetection/olga/objectgraphedgetest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    EDLTest edlTest;

    ObjectGraphEdgeTest objectGraphEdgeTest;

    return   QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv)
           | QTest::qExec(&objectGraphEdgeTest, argc, argv);
}

