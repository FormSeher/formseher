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

        o.addLine(line1);
        o.addLine(line2);

        QVERIFY(2 == o.getLines().size());
        QVERIFY(cv::Point2i(1, 2) == o.getLines().at(0)->getStart());
        QVERIFY(cv::Point2i(7, 9) == o.getLines().at(1)->getEnd());

        QVERIFY(cv::Rect(1, 2, 6, 7) == o.getBoundingBox());
    }

    void toStringTest()
    {
        Object o;
        o.setName("Fancy object");
        o.addLine(Line(10, 2, 3, 4));
        o.addLine(Line(5, 666, 7, 8));

        std::string serialized = o.toString();

        QVERIFY("Fancy object:10,2,3,4;5,666,7,8;" == serialized);
    }

    void fromStringTest()
    {
        std::string serialized = "Fancy object:10,2,3,4;5,666,7,8;";

        Object o;
        o.fromString(serialized);

        QVERIFY("Fancy object" == o.getName());
        QVERIFY(2 == o.getLines().size());

        auto lines = o.getLines();
        QVERIFY(cv::Point2i(10, 2) == lines.at(0)->getStart());
        QVERIFY(cv::Point2i( 3, 4) == lines.at(0)->getEnd());
        QVERIFY(cv::Point2i( 5, 666) == lines.at(1)->getStart());
        QVERIFY(cv::Point2i( 7, 8) == lines.at(1)->getEnd());
    }
};

#endif // FS_OBJECTTEST_H
