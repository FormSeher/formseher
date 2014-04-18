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
        QVERIFY(VERTICAL == edl->getDirection(degreeToRad(0)));
        QVERIFY(VERTICAL == edl->getDirection(degreeToRad(20)));
        QVERIFY(VERTICAL == edl->getDirection(M_PI));
        QVERIFY(VERTICAL == edl->getDirection(degreeToRad(199)));

        QVERIFY(HORIZONTAL == edl->getDirection(degreeToRad(90)));
        QVERIFY(HORIZONTAL == edl->getDirection(degreeToRad(270)));
    }

    void routeAnchorsTest()
    {
        cv::Mat_<uchar> magnitudes = cv::Mat::zeros(5, 5, CV_8U);
        magnitudes(1, 0) = 140;
        magnitudes(1, 1) = 150;
        magnitudes(1, 2) = 143;
        magnitudes(1, 3) = 145;

        cv::Mat_<double> angles = cv::Mat::zeros(magnitudes.rows, magnitudes.cols, magnitudes.type());
        angles(1, 1) = 0.5 * M_PI / 180.0d;
        angles(1, 2) = 0.5 * M_PI / 180.0d;
        angles(1, 3) = 0.5 * M_PI / 180.0d;

        std::vector<cv::Point> anchorPoints;
        anchorPoints.push_back(cv::Point(1, 0));
        anchorPoints.push_back(cv::Point(3, 1));

        double angleTolerance = 21.5 * M_PI / 180.0d;

        std::vector<Line> result;

        edl->routeAnchors(angleTolerance, magnitudes, angles, anchorPoints, result);

        // Check the result
        QVERIFY(1 == result.size());

        Line& line = result.at(0);
        QVERIFY(cv::Point2d(0, 1) == line.getStart());
        QVERIFY(cv::Point2d(3, 1) == line.getEnd());
    }

    void findNextPointTest()
    {
        cv::Mat_<uchar> magnitudes = cv::Mat::zeros(5, 5, CV_8U);
        magnitudes(1, 1) = 150;
        magnitudes(1, 2) = 140;
        magnitudes(1, 3) = 143;
        magnitudes(2, 2) = 155;
        magnitudes(3, 2) = 140;
        magnitudes(4,  3) = 120;

        int mainDirection = HORIZONTAL;
        int subDirection = -1;
        cv::Point currentPoint(2, 1);

        cv::Point* nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(1 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        QVERIFY(150 == magnitudes(*nextPoint));
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(1 == nextPoint->y);
        QVERIFY(143 == magnitudes(*nextPoint));
        delete nextPoint;

        mainDirection = VERTICAL;
        subDirection = -1;
        currentPoint.x = 2;
        currentPoint.y = 3;

        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(2 == nextPoint->x);
        QVERIFY(2 == nextPoint->y);
        QVERIFY(155 == magnitudes(*nextPoint));
        delete nextPoint;

        subDirection = +1;
        nextPoint = edl->findNextPoint(&currentPoint, mainDirection, subDirection, magnitudes);
        QVERIFY(3 == nextPoint->x);
        QVERIFY(4 == nextPoint->y);
        QVERIFY(120 == magnitudes(*nextPoint));
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

    void isOutOfBoundsTest()
    {
        cv::Mat mat = cv::Mat::zeros(2, 2, CV_8U);

        cv::Point point(-1, 0);
        QVERIFY(true == edl->isOutOfBounds(&point, mat));

        point = cv::Point(0, 0);
        QVERIFY(false == edl->isOutOfBounds(&point, mat));

        point = cv::Point(2, 2);
        QVERIFY(false == edl->isOutOfBounds(&point, mat));

        point = cv::Point(2, 3);
        QVERIFY(true == edl->isOutOfBounds(&point, mat));

        point = cv::Point(3, 2);
        QVERIFY(true == edl->isOutOfBounds(&point, mat));

        point= cv::Point(1, -1);
        QVERIFY(true == edl->isOutOfBounds(&point, mat));
    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL* edl;

    double degreeToRad(double degree)
    {
        return degree * M_PI / 180.0;
    }
};

#endif // EDLTEST_H
