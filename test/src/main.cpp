#include <QtTest>

#include "algorithmtest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    AlgorithmTest algorithmTest;

    return QTest::qExec(&algorithmTest, argc, argv);
}

