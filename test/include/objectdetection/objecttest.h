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
    void ratingTest()
    {
        Object o;
        o.setRating(12.25);
        QVERIFY(12.25f == o.getRating());
    }
};

#endif // FS_OBJECTTEST_H
