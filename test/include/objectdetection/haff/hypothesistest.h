/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

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

        h.calculateAngleRating();
        QCOMPARE(h.angleRating, 1.0d);
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

        h.calculateAngleRating();
        QCOMPARE(h.angleRating, 0.0d);
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

        h.calculateAngleRating();
        QCOMPARE(h.angleRating, 0.780999056761673);
    }

    void calculateCentersTest()
    {
        Line objectLine1(1, 1, 3, 1);
        Line objectLine2(3, 2, 3, 4);

        Line modelLine1(1, 1, 4, 1);
        Line modelLine2(4, 1, 2, 3);
        Line modelLine3(2, 3, 1, 1);

        Hypothesis h(0);
        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);
        h.addLineMatch(nullptr,      &modelLine3);

        std::pair<cv::Point2d, cv::Point2d> centers = h.calculateCenters();

        QCOMPARE(centers.first, cv::Point2d(2.5, 2.0));
        // Result has to be 2.33... and 1.66..
        QCOMPARE(centers.second, cv::Point2d(7.0/3.0, 5.0/3.0));
    }

    void calculateCoverageRatingPerfectMatch()
    {
        Line objectLine1(3,1,7,1);
        Line modelLine1(3,1,7,1);

        Hypothesis h(0);
        h.addLineMatch(&objectLine1,&modelLine1);
        h.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating,1.0);
    }

    void calculateCoverageRatingWorstMatch()
    {
        Line objectLine1(1,1,9,1);
        Line modelLine1(3,1,7,1);

        Hypothesis h(0);
        h.addLineMatch(&objectLine1,&modelLine1);

        h.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating, 0.0);
    }

    // Test what happens if object line length greatly exceeds model line length
    void calculateCoverageRatingBigErrors()
    {
        // Object line longer than model line
        Line objectLine(1, 1, 13, 1);
        Line modelLine(0, 0, 4, 0);

        Hypothesis h(0);
        h.addLineMatch(&objectLine, &modelLine);
        h.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating, 0.0);

        // Object line shorter than model line
        Line objectLine2(1, 1, 2, 1);
        Line modelLine2(0, 0, 3, 0);

        Hypothesis h2(0);
        h2.addLineMatch(&objectLine2, &modelLine2);
        h2.scaleFactor = 1;
        h2.calculateCoverageRating();

        QCOMPARE(h.coverRating, 0.0);
    }

    void calculateCoverageRatingHalfMatch()
    {
        // Object line longer than model line
        Line objectLine(0, 0, 6, 0);
        Line modelLine(0, 0, 4, 0);

        Hypothesis h(0);
        h.addLineMatch(&objectLine, &modelLine);
        h.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating, 0.5);

        // Object line shorter than model line
        Line objectLine2(0, 0, 2, 0);

        Hypothesis h2(0);
        h2.addLineMatch(&objectLine2, &modelLine);
        h2.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating, 0.5);
    }

    void calcCoverageRatingZeroLength()
    {
        Line objectLine(0, 0, 1, 0);
        Line modelLine(0, 0, 0, 0);

        Hypothesis h(0);
        h.addLineMatch(&objectLine, &modelLine);
        h.scaleFactor = 1;
        h.calculateCoverageRating();

        QCOMPARE(h.coverRating, 1.0);
    }

    void calculateCoverageRatingComplexCase()
    {
        Line objectLine1(1, 1, 4, 1); // length = 3
        Line objectLine2(1, 2, 1, 6); // length = 4
        Line modelLine1(3, 3, 3, 6); // length = 3
        Line modelLine2(4, 4, 6, 4); // length = 2

        Hypothesis h(0);
        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);
        h.scaleFactor = 1.5;
        h.calculateCoverageRating();

        // Result has to be 2.0 / 3.0 = 0.66666....
        QCOMPARE(h.coverRating, 2.0 / 3.0);
    }

    void calcPositionRatingComplexCase()
    {
        Line objectLine1(1, 1, 1, 4);
        Line objectLine2(2, 4, 6, 4);
        Line objectLine3(2, 2, 5, 3);

        Line modelLine1(1, 6, 1, 9);
        Line modelLine2(2, 10, 5, 10);
        Line modelLine3(3, 6, 6, 8);

        Hypothesis h(0);
        h.addLineMatch(&objectLine1, &modelLine1);
        h.addLineMatch(&objectLine2, &modelLine2);
        h.addLineMatch(&objectLine3, &modelLine3);
        h.scaleFactor = 1.5;
        h.calculatePositionRating();

//        printf("%.16f\n", h.positionRating);
        QCOMPARE(h.positionRating, 0.4774498596849225);
    }

    void calcPositionRatingZeroDistance()
    {
        Line line1(1, 1, 4, 1);
        Line line2(1, 3, 4, 3);
        Line line3(1, 2, 4, 2);

        Hypothesis h(0);
        h.addLineMatch(&line1, &line1);
        h.addLineMatch(&line2, &line2);
        h.addLineMatch(&line3, &line3);
        h.scaleFactor = 1;
        h.calculatePositionRating();

        QCOMPARE(h.positionRating, 1.0);
    }

    void copyConstructorTest()
    {
        const Model model;
        Hypothesis h1(&model, 1.5, 2.5);
        Line l1(0,0,10,10), l2(10,10,20,20), l3(20,20,30,30), l4(30,30,40,40);

        h1.addLineMatch(&l1, &l2);

        Hypothesis h2(h1);

        h1.addLineMatch(&l3, &l4);

        QCOMPARE (h1.getModel(), &model);
        QCOMPARE (h2.getModel(), &model);

        QCOMPARE(h1.angleWeight, 1.5);
        QCOMPARE(h2.angleWeight, 1.5);

        QCOMPARE(h1.coverWeight, 2.5);
        QCOMPARE(h2.coverWeight, 2.5);

        QVERIFY(h1.containsLine(&l1));
        QVERIFY(h2.containsLine(&l1));
        QVERIFY(h1.containsLine(&l3));
        QVERIFY( ! h2.containsLine(&l3));
    }

    void lineMatchMapTest()
    {
        Hypothesis h(0);
        Line l1(0,0,10,10), l2(10,10,20,20), l3(20,20,30,30), l4(30,30,40,40);

        h.addLineMatch(&l1, &l2);
        h.addLineMatch(&l2, &l3);
        h.addLineMatch(&l3, &l4);

        QVERIFY(*(*h.lineMatchMap.begin()).first == l1);
        QVERIFY(*(*h.lineMatchMap.begin()).second == l2);

        QVERIFY(*(*++h.lineMatchMap.begin()).first == l2);
        QVERIFY(*(*++h.lineMatchMap.begin()).second == l3);

        QVERIFY(*(*++++h.lineMatchMap.begin()).first == l3);
        QVERIFY(*(*++++h.lineMatchMap.begin()).second == l4);
    }

    void scaleFactorTest()
    {
        Hypothesis h1(0);
        Line ol1(0,0,10,10), ml1(0,0,10,10);

        h1.addLineMatch(&ol1, &ml1);
        h1.calculateScale();
        QVERIFY(h1.scaleFactor == 1);

        Hypothesis h2(0);
        Line ol2(0,0,0,10), ml2(0,0,0,20);
        Line ol3(0,0,10,0), ml3(0,0,20,0);

        h2.addLineMatch(&ol2, &ml2);
        h2.addLineMatch(&ol3, &ml3);
        h2.calculateScale();

//        qDebug() << h2.scaleFactor;

        QVERIFY(h2.scaleFactor == 0.5);
    }
};

#endif // FS_HYPOTHESISTEST_H
