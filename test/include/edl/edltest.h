#ifndef EDLTEST_H
#define EDLTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include <opencv2/core/core.hpp>

#include <iostream>

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

    void routeAnchorsTest()
    {
        cv::Mat magnitudes(5, 5, CV_32F);

        cv::Mat_<double> _magnitudes(magnitudes);
        _magnitudes(1, 1) = 15.0;
        _magnitudes(1, 2) = 14.0;
        _magnitudes(1, 3) = 14.3;

        cv::Mat angles(5, 5, CV_32F);
        cv::Mat_<double> _angles(angles);
        _angles(1, 1) = 0.5;
        _angles(1, 2) = 0.5;
        _angles(1, 3) = 0.5;

        std::vector<cv::Point*> anchorPoints;
        anchorPoints.push_back(new cv::Point(1, 1));
        anchorPoints.push_back(new cv::Point(1, 3));

        std::vector<Line*> result;

        edl->routeAnchors(magnitudes, angles, anchorPoints, result);

        for(auto anchorPoint : anchorPoints)
            delete anchorPoint;
    }

    void walkFromAnchorTest()
    {

    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;
};

#endif // EDLTEST_H
