#include <QtTest>

#include "algorithmtest.h"
#include "linetest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    AlgorithmTest algorithmTest;
    LineTest lineTest;

    return QTest::qExec(&algorithmTest, argc, argv) |
            QTest::qExec(&lineTest, argc, argv);
}

