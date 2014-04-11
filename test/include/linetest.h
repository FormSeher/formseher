#ifndef LINETEST_H
#define LINETEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "line.h"

class LineTest : public QObject
{
    Q_OBJECT

private slots:
    void test1()
    {
        Line line(0.5, 1.0, 1.5, 2.0);
        QVERIFY(0.5 == line.getStart().x);
        QVERIFY(1.0 == line.getStart().y);
        QVERIFY(1.5 == line.getEnd().x);
        QVERIFY(2.0 == line.getEnd().y);
    }

    void test2()
    {
        cv::Point2d start(0.5, 1.0);
        cv::Point2d end(1.5, 2.0);

        Line line(start, end);

        QVERIFY(0.5 == line.getStart().x);
        QVERIFY(1.0 == line.getStart().y);
        QVERIFY(1.5 == line.getEnd().x);
        QVERIFY(2.0 == line.getEnd().y);
    }
};

#endif // LINETEST_H
