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
    void test1()
    {
        Line line(1, 2, 3, 4);
        QVERIFY(1 == line.getStart().x);
        QVERIFY(2 == line.getStart().y);
        QVERIFY(3 == line.getEnd().x);
        QVERIFY(4 == line.getEnd().y);
    }

    void test2()
    {
        cv::Point2i start(1, 2);
        cv::Point2i end(3, 4);

        Line line(start, end);

        QVERIFY(1 == line.getStart().x);
        QVERIFY(2 == line.getStart().y);
        QVERIFY(3 == line.getEnd().x);
        QVERIFY(4 == line.getEnd().y);
    }
};

#endif // FS_LINETEST_H
