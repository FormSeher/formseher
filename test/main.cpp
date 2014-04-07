#include <QtTest>

#include "algorithmtest.h"
#include "mysecondtest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    AlgorithmTest algorithmTest;
    MySecondTest mySecondTest;

    return QTest::qExec(&algorithmTest, argc, argv)
         | QTest::qExec(&mySecondTest, argc, argv);
}

