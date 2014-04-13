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
        cv::Mat angles = (cv::Mat_<double>(2, 2) << 0.0175, 1.2217, 2.9671, 4.8869);

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
        cv::Mat_<double> magnitudes = cv::Mat::zeros(5, 5, CV_64F);
        magnitudes(1, 1) = 15.0;
        magnitudes(1, 2) = 14.0;
        magnitudes(1, 3) = 14.3;

        cv::Mat_<double> angles = cv::Mat::zeros(magnitudes.rows, magnitudes.cols, magnitudes.type());
        angles(1, 1) = 0.5 * M_PI / 180.0d;
        angles(1, 2) = 0.5 * M_PI / 180.0d;
        angles(1, 3) = 0.5 * M_PI / 180.0d;

        std::vector<cv::Point*> anchorPoints;
        anchorPoints.push_back(new cv::Point(1, 1));
        anchorPoints.push_back(new cv::Point(3, 1));

        double angleTolerance = 21.5 * M_PI / 180.0d;

        std::vector<Line*> result;

        edl->routeAnchors(angleTolerance, magnitudes, angles, anchorPoints, result);

        // Check the result
        QVERIFY(1 == result.size());

        Line* line = result.at(0);
        QVERIFY(cv::Point2d(1, 1) == line->getStart());
        QVERIFY(cv::Point2d(3, 1) == line->getEnd());


        for(auto anchorPoint : anchorPoints)
            delete anchorPoint;

        for(auto line : result)
            delete line;
    }

    void walkFromAnchorTest()
    {

    }

    void findNextPointTest()
    {
        cv::Mat_<double> magnitudes = cv::Mat::zeros(5, 5, CV_64F);
        magnitudes(1, 1) = 15.0;
        magnitudes(1, 2) = 14.0;
        magnitudes(1, 3) = 14.3;
        magnitudes(2, 2) = 15.5;
        magnitudes(3, 2) = 14.0;
        magnitudes(4,  3) = 12.0;

        int mainDirection = HORIZONTAL;
        int subDirection = -1;
        cv::Point currentPoint(2, 1);

        cv::Point* nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(1 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        QVERIFY(15.0 == magnitudes(*nextPoint));
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        QVERIFY(14.3 == magnitudes(*nextPoint));
        delete nextPoint;

        mainDirection = VERTICAL;
        subDirection = -1;
        currentPoint.x = 2;
        currentPoint.y = 3;

        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(2 == nextPoint->x);
        QVERIFY(2 == nextPoint->y);
        QVERIFY(15.5 == magnitudes(*nextPoint));
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(4 == nextPoint->y);
        QVERIFY(12.0 == magnitudes(*nextPoint));
        delete nextPoint;
    }

    void isAlignedTest()
    {
        double angleTolerance = 21.5 * M_PI / 180.0d;

        // test aligned
        QVERIFY(true  == edl->isAligned( 0,   0, angleTolerance));
        QVERIFY(true  == edl->isAligned( 21.5 * M_PI / 180.0d, 0, angleTolerance));
        QVERIFY(true  == edl->isAligned(180 * M_PI / 180.0d,  0, angleTolerance));
        QVERIFY(true  == edl->isAligned(90 * M_PI / 180.0d,  270 * M_PI / 180.0d, angleTolerance));
        // Test not aligned
        QVERIFY(false == edl->isAligned( 22 * M_PI / 180.0d,   0, angleTolerance));
        QVERIFY(false == edl->isAligned( 45 * M_PI / 180.0d, 23 * M_PI / 180.0d, angleTolerance));
        QVERIFY(false == edl->isAligned(100 * M_PI / 180.0d, 200 * M_PI / 180.0d, angleTolerance));
    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;
};

#endif // EDLTEST_H
