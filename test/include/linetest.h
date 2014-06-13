#ifndef FS_LINETEST_H
#define FS_LINETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <iostream>

#include "line.h"

using namespace formseher;

class LineTest : public QObject
{
    Q_OBJECT

private slots:
    void constructorTest1()
    {
        Line line(1, 2, 3, 4);
        QVERIFY(1 == line.getStart().x);
        QVERIFY(2 == line.getStart().y);
        QVERIFY(3 == line.getEnd().x);
        QVERIFY(4 == line.getEnd().y);
    }

    void constructorTest2()
    {
        cv::Point2i start(1, 2);
        cv::Point2i end(3, 4);

        Line line(start, end);

        QVERIFY(1 == line.getStart().x);
        QVERIFY(2 == line.getStart().y);
        QVERIFY(3 == line.getEnd().x);
        QVERIFY(4 == line.getEnd().y);
    }


    void positionVectorTest()
    {
        Line line(1, 2, 3, 4);
        QVERIFY(1 == line.getPositionVector()[0]);
        QVERIFY(2 == line.getPositionVector()[1]);
    }

    void directionVectorTest()
    {
        Line line(1, 2, 3, 4);
        QVERIFY( 2.0 / std::sqrt( 2 * 2 + 2 * 2) == line.getDirectionVector()[0]);
        QVERIFY( 2.0 / std::sqrt( 2 * 2 + 2 * 2) == line.getDirectionVector()[1]);
    }

    void lengthTest()
    {
        Line line(1, 2, 3, 4);
        QVERIFY( std::sqrt(2 * 2 + 2 * 2) == line.getLength() );
    }

    void perpendicularPointTest()
    {
        Line line1(-4, 20, 4, 20);
        QVERIFY ( 0 == line1.getPerpendicularPoint().x );
        QVERIFY ( 20 == line1.getPerpendicularPoint().y );

        Line line2(-4, 20, 4, -20);
        QVERIFY ( 0 == line2.getPerpendicularPoint().x );
        QVERIFY ( 0 == line2.getPerpendicularPoint().y );

        Line line3(3, 7, 0, 10);
        QVERIFY ( 5 == line3.getPerpendicularPoint().x );
        QVERIFY ( 5 == line3.getPerpendicularPoint().y );
    }

    void centerPointTest()
    {
        Line line1(0, 0, 2, 2);
        QCOMPARE(line1.getCenterPoint(), cv::Point2f(1, 1));

        Line line2(-1, 1, 1, -1);
        QCOMPARE(line2.getCenterPoint(), cv::Point2f(0, 0));
    }
    void getPerpendicularDistanceToOriginTest()
    {
        Line line1(-4, 20, 4, 20);
        QVERIFY ( 20 == line1.getPerpendicularDistanceToOrigin() );

        Line line2(-4, 20, 4, -20);
        QVERIFY ( 0 == line2.getPerpendicularDistanceToOrigin() );

        Line line3(3, 7, 0, 10);
        QVERIFY ( std::sqrt(5*5+5*5) == line3.getPerpendicularDistanceToOrigin() );
    }

    void setPerpendicularTest()
    {
        Line line(0, 0, 0, 0);
        cv::Point2i testPoint = cv::Point2i(20,40);
        line.setPerpendicular(1.435, testPoint);

        QVERIFY ( 1.435 == line.getPerpendicularDistanceToOrigin() );
        QVERIFY ( 20 == line.getPerpendicularPoint().x);
        QVERIFY ( 40 == line.getPerpendicularPoint().y);

    }

    void getPerpendicularDistanceToStartTest()
    {
        Line line1(-4, 20, 4, 20);
        QVERIFY ( 4 == line1.getPerpendicularDistanceToStart() );

        Line line2(2, 20, 10, 20);
        QVERIFY ( 2 == line2.getPerpendicularDistanceToStart() );

        Line line3(3, 7, 0, 10);
        QVERIFY ( std::sqrt(-2*-2+2*2) == line3.getPerpendicularDistanceToStart() );
    }

    void getPerpendicularDistanceToEndTest()
    {
        Line line1(-4, 20, 4, 20);
        QVERIFY ( 4 == line1.getPerpendicularDistanceToStart() );

        Line line2(2, 20, 10, 20);
        QVERIFY ( 10 == line2.getPerpendicularDistanceToEnd() );

        Line line3(3, 7, 0, 10);
        QVERIFY ( std::sqrt(-5*-5+5*5) == line3.getPerpendicularDistanceToEnd() );
    }

};

#endif // FS_LINETEST_H
