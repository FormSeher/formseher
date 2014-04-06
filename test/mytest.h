#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QtTest/QtTest>

class MyTest : public QObject
{
    Q_OBJECT
 private slots:
     void mySecondTest()
     { QVERIFY(1 != 2); }
};

#endif // MYTEST_H
