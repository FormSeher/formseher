#include <QtTest>

#include "mytest.h"
#include "mysecondtest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MyTest myTest;
    MySecondTest mySecondTest;

    return QTest::qExec(&myTest, argc, argv)
         | QTest::qExec(&mySecondTest, argc, argv);
}

