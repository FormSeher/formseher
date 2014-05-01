#include <QtTest>

#include "linetest.h"
#include "edl/edltest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LineTest lineTest;
    EDLTest edlTest;

    return   QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv);
}

