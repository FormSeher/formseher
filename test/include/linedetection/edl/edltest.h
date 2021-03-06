/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

#ifndef FS_EDLTEST_H
#define FS_EDLTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include <opencv2/core/core.hpp>

#include <iostream>

#include "mathutil.h"

// brute force everything public (don't do this at home kids!)
#undef private
#undef protected
#define private public
#define protected public

#include "linedetection/edl/edl.h"

// Restore visibilities
#undef private
#undef protected
#define protected protected
#define private private

using namespace formseher;

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
        QVERIFY(VERTICAL == edl->getDirection(math::m_pi));
        QVERIFY(VERTICAL == edl->getDirection(degreeToRad(199)));

        QVERIFY(HORIZONTAL == edl->getDirection(degreeToRad(90)));
        QVERIFY(HORIZONTAL == edl->getDirection(degreeToRad(270)));
    }

    void routeAnchorsTest()
    {
        edl->minLineLength = 2;

        cv::Mat_<uchar> magnitudes = cv::Mat::zeros(6, 10, CV_8U);
        magnitudes(2, 1) = 139;
        magnitudes(3, 1) = 139;
        magnitudes(4, 1) = 140;

        magnitudes(2, 2) = 145;
        magnitudes(3, 2) = 170;
        magnitudes(4, 2) = 139;

        magnitudes(1, 3) = 140;
        magnitudes(2, 3) = 160;
        magnitudes(3, 3) = 170;

        magnitudes(1, 4) = 150;
        magnitudes(2, 4) = 120;

        magnitudes(1, 5) = 140;
        magnitudes(2, 5) = 145;

        magnitudes(1, 6) = 146;
        magnitudes(2, 6) = 110;

        magnitudes(0, 7) = 120;
        magnitudes(1, 7) = 120;
        magnitudes(2, 7) = 130;
        magnitudes(4, 7) = 120;

        magnitudes(2, 8) = 115;
        magnitudes(3, 8) = 120;

        cv::Mat_<double> angles = cv::Mat::zeros(magnitudes.rows, magnitudes.cols, magnitudes.type());
        for(int row = 0; row < angles.rows; ++row)
            for(int col = 0; col < 4; ++col)
                angles(row, col) = degreeToRad(113);

        for(int row = 0; row < angles.rows; ++row)
            for(int col = 4; col < 7; ++col)
                angles(row, col) = degreeToRad(90);

        for(int row = 0; row < angles.rows; ++row)
            for(int col = 7; col < angles.cols; ++col)
                angles(row, col) = degreeToRad(65);

        std::vector<cv::Point> anchorPoints;
        anchorPoints.push_back(cv::Point(4, 1));
        anchorPoints.push_back(cv::Point(8, 3));

        double angleTolerance = 21.5 * math::m_pi / 180.0d;

        std::vector<Line> result;

        edl->routeAnchors(angleTolerance, magnitudes, angles, anchorPoints, result);

        // Check the result
        QVERIFY(3 == result.size());

        Line line = result.at(0);
        QVERIFY(cv::Point2i(4, 1) == line.getStart());
        QVERIFY(cv::Point2i(6, 1) == line.getEnd());

        line = result.at(1);
        QVERIFY(cv::Point2i(1, 4) == line.getStart());
        QVERIFY(cv::Point2i(3, 2) == line.getEnd());

        line = result.at(2);
        QVERIFY(cv::Point2i(7, 2) == line.getStart());
        QVERIFY(cv::Point2i(8, 3) == line.getEnd());
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
        double angleTolerance = 21.5 * math::m_pi / 180.0d;

        // test aligned
        QVERIFY(true  == edl->isAligned( 0,   0, angleTolerance));
        QVERIFY(true  == edl->isAligned( 21.5 * math::m_pi / 180.0d, 0, angleTolerance));
        QVERIFY(true  == edl->isAligned(180 * math::m_pi / 180.0d,  0, angleTolerance));
        QVERIFY(true  == edl->isAligned(90 * math::m_pi / 180.0d,  270 * math::m_pi / 180.0d, angleTolerance));
        // Test not aligned
        QVERIFY(false == edl->isAligned( 22 * math::m_pi / 180.0d,   0, angleTolerance));
        QVERIFY(false == edl->isAligned( 45 * math::m_pi / 180.0d, 23 * math::m_pi / 180.0d, angleTolerance));
        QVERIFY(false == edl->isAligned(100 * math::m_pi / 180.0d, 200 * math::m_pi / 180.0d, angleTolerance));
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
        return degree * math::m_pi / 180.0;
    }
};

#endif // FS_EDLTEST_H
