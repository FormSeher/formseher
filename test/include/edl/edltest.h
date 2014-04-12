#ifndef EDLTEST_H
#define EDLTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include <opencv2/core/core.hpp>

// brute force everything public (don't do this at home kids!)
#undef private
#undef protected
#define private public
#define protected public

#include "edl/edl.h"

// Restore visibilities
#undef private
#undef protected
#define protected protected
#define private private

class EDLTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        edl = new EDL();
    }

    void getDirectionTest()
    {
        cv::Mat angles = (cv::Mat_<double>(2, 2) << 1, 170, 70, 280);

        cv::Point point(0, 0);
        QVERIFY(HORIZONTAL == edl->getDirection(point, angles));

        point.x = 1;
        QVERIFY(VERTICAL == edl->getDirection(point, angles));

        point.x = 0;
        point.y = 1;
        QVERIFY(HORIZONTAL == edl->getDirection(point, angles));

        point.x = 1;
        QVERIFY(VERTICAL == edl->getDirection(point, angles));
    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;
};

#endif // EDLTEST_H
