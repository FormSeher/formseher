#ifndef POINTERCOMPARETEST_H
#define POINTERCOMPARETEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "pointercompare.h"

class PointerCompareTest : public QObject
{
Q_OBJECT

private slots:
    void compareTest()
    {
        PointerCompare<int> cmp;

        int x = 0;
        int y = 1;

        QVERIFY(cmp(&x, &y));
        QVERIFY(!cmp(&y, &x));
    }
};

#endif // POINTERCOMPARETEST_H
