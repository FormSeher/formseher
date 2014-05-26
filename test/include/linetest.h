#ifndef FS_LINETEST_H
#define FS_LINETEST_H

#include <QObject>
#include <QtTest/QtTest>

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

};

#endif // FS_LINETEST_H
