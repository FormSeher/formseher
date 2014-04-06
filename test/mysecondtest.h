#ifndef MYSECONDTEST_H
#define MYSECONDTEST_H

#include <QObject>
#include <QtTest/QtTest>

class MySecondTest : public QObject
{
    Q_OBJECT
 private slots:
     void myFirstTest()
     { QVERIFY(1 == 1); }
};

#endif // MYSECONDTEST_H
