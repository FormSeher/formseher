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

//    void routeAnchorsTest()
//    {
//        cv::Mat_<double> magnitudes = cv::Mat::zeros(5, 5, CV_64F);
//        magnitudes(1, 1) = 15.0;
//        magnitudes(1, 2) = 14.0;
//        magnitudes(1, 3) = 14.3;

//        cv::Mat_<double> angles = cv::Mat::zeros(magnitudes.rows, magnitudes.cols, magnitudes.type());
//        angles(1, 1) = 0.5;
//        angles(1, 2) = 0.5;
//        angles(1, 3) = 0.5;

//        std::vector<cv::Point*> anchorPoints;
//        anchorPoints.push_back(new cv::Point(1, 1));
//        anchorPoints.push_back(new cv::Point(1, 3));

//        std::vector<Line*> result;

//        edl->routeAnchors(magnitudes, angles, anchorPoints, result);

//        for(auto anchorPoint : anchorPoints)
//            delete anchorPoint;

//        for(auto line : result)
//            delete line;
//    }

    void walkFromAnchorTest()
    {

    }

    void findNextPointTest()
    {
        cv::Mat_<double> magnitudes = cv::Mat::zeros(5, 5, CV_64F);
        magnitudes(1, 1) = 15.0;
        magnitudes(2, 1) = 14.0;
        magnitudes(3, 1) = 14.3;
        magnitudes(2, 2) = 15.0;
        magnitudes(2, 3) = 14.0;
        magnitudes(3, 4) = 12.0;

        int mainDirection = HORIZONTAL;
        int subDirection = -1;
        cv::Point currentPoint(2, 1);

        cv::Point* nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(1 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        delete nextPoint;

        mainDirection = VERTICAL;
        subDirection = -1;
        currentPoint.x = 2;
        currentPoint.y = 3;

        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(2 == nextPoint->x);
        QVERIFY(2 == nextPoint->y);
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(4 == nextPoint->y);
        delete nextPoint;
    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;
};

#endif // EDLTEST_H
