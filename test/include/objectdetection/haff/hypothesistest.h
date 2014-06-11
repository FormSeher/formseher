#ifndef FS_HYPOTHESISTEST_H
#define FS_HYPOTHESISTEST_H

#include <QtTest/QtTest>
#include <QObject>

// brute force private to public (don't do this at home kids!)
#undef private
#define private public

#include "objectdetection/haff/hypothesis.h"

// Restore visibilities
#undef private
#define private private

using namespace formseher;

class HypothesisTest : public QObject
{
Q_OBJECT

private slots:
    void containsLineTest()
    {
        Hypothesis h(0);

        Line l1(1, 2, 3, 4);
        Line l2(1, 2, 3, 4);

        h.addLineMatch(&l1, &l2);

        QVERIFY( h.containsLine(&l1));
        QVERIFY(!h.containsLine(&l2));
    }

    void calculateAngleRating_perfectMatch()
    {
        Hypothesis h(0);

        Line modelLine1(1, 1, 1, 5);
        Line modelLine2(3, 4, 6, 1);

        Line objectLine1(modelLine1);
        // objectLine2 == inverse of modelLine2
        Line objectLine2(6, 1, 3, 4);

        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);

        QCOMPARE(h.calculateAngleRating(), 1.0d);
    }

    void calculateAngleRating_noMatch()
    {
        Hypothesis h(0);

        Line modelLine1(2, 4, 7, 4);
        Line modelLine2(2, 2, 7, 2);

        Line objectLine1(modelLine1);
        // objectLine2 |_ modelLine2
        Line objectLine2(5, 1, 5, 8);

        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);

        QCOMPARE(h.calculateAngleRating(), 0.0d);
    }

    void calculateAngleRationg_partialMatch()
    {
        Hypothesis h(0);

        Line modelLine1(2, 3, 2, 7);
        Line modelLine2(3, 3, 7, 3);
        Line modelLine3(8, 7, 3, 7);

        Line objectLine1(modelLine1);
        // objectLine2 /_ modelLine2 == 45°
        Line objectLine2(3, 3, 8, 0);
        // objectLine3 || modelLine3
        Line objectLine3(3, 7, 7, 7);

        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);
        h.addLineMatch(&objectLine3, &modelLine3);

        QCOMPARE(h.calculateAngleRating(), 0.780999056761673);
    }
};

#endif // FS_HYPOTHESISTEST_H
