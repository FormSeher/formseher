#ifndef FS_OBJECTTEST_H
#define FS_OBJECTTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "objectdetection/object.h"

using namespace formseher;

class ObjectTest : public QObject
{
Q_OBJECT

private slots:
    void copyConstructorTest()
    {
        Object o1;
        o1.setName("m1");
        o1.addLine(Line(1, 1, 2, 2));
        o1.setRating(22.13);

        Object o2(o1);

        // Check if parent copy constructor was called
        QVERIFY(o1.getLines().at(0) != o2.getLines().at(0));

        QVERIFY(o1.getRating() == o2.getRating());
    }

    void ratingTest()
    {
        Object o;
        o.setRating(12.25);
        QVERIFY(12.25f == o.getRating());
    }
};

#endif // FS_OBJECTTEST_H
