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
    void copyConstructorTest()
    {
        Object o1;
        o1.setName("o1");
        o1.addLine(Line(1, 1, 2, 2));

        Object o2(o1);

        QVERIFY(o1.getName() == o2.getName());
        QVERIFY(o1.getBoundingBox() == o2.getBoundingBox());

        QVERIFY(o1.getLines().size() == o2.getLines().size());

        const Line* l1 = o1.getLines().at(0);
        const Line* l2 = o2.getLines().at(0);

        // Check if pointers are different
        QVERIFY(l1 != l2);
        // Check if line objects are equal
        QVERIFY(l1->getStart() == l2->getStart());
        QVERIFY(l1->getEnd() == l2->getEnd());
    }

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

    void ratingTest()
    {
        Object o;
        o.setRating(12.25);
        QVERIFY(12.25f == o.getRating());
    }
};

#endif // FS_OBJECTTEST_H
