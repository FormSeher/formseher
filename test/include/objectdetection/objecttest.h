#ifndef FS_OBJECTTEST_H
#define FS_OBJECTTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include <opencv2/core/core.hpp>

#include "objectdetection/object.h"
#include "line.h"

using namespace formseher;

class ObjectTest : public QObject
{
Q_OBJECT

private slots:
    void nameTest()
    {
        Object o;
        o.setName("This is object!");
        QVERIFY("This is object!" == o.getName());
    }

    void addLineTest()
    {
        Object o;
        Line line1(1, 2, 3, 4);
        Line line2(5, 6, 7, 9);

        o.addLine(&line1);
        o.addLine(&line2);

        QVERIFY(2 == o.getLines().size());
        QVERIFY(cv::Point2i(1, 2) == o.getLines().at(0)->getStart());
        QVERIFY(cv::Point2i(7, 9) == o.getLines().at(1)->getEnd());

        QVERIFY(cv::Rect(1, 2, 6, 7) == o.getBoundingBox());
    }
};

#endif // FS_OBJECTTEST_H
