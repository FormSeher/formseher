#include <QtTest>

#include "algorithmtest.h"
#include "linetest.h"
#include "edl/edltest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    AlgorithmTest algorithmTest;
    LineTest lineTest;
    EDLTest edlTest;

    return QTest::qExec(&algorithmTest, argc, argv)
           | QTest::qExec(&lineTest, argc, argv)
           | QTest::qExec(&edlTest, argc, argv);
}

