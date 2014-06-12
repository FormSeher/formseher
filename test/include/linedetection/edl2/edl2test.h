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

#include "linedetection/edl2/edl2.h"

// Restore visibilities

#undef private
#undef protected
#define protected protected
#define private private

using namespace formseher;

class EDL2Test : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        edl = new EDL2();
    }

    void calcGradTest()
    {
        //Create an image

        cv::Mat_<uchar> image = (cv::Mat_<uchar>(4,5) <<    0,       0,       0,      0,       0,
                                                            1,      11,     255,     21,       0,
                                                            0,      12,     254,     22,       0,
                                                            0,       0,       0,      0,       0);

        // define output

        cv::Mat_<uchar> test_gradientMagnitudes = (cv::Mat_<uchar>(image.rows,image.cols) <<     0,    0,      0,      0,      0,
                                                                                                 0,    65,     31,     72,     0,
                                                                                                 0,    65,     31,     71,     0,
                                                                                                 0,    0,      0,      0,      0);

        cv::Mat_<short> test_dx = (cv::Mat_<short>(image.rows,image.cols) <<                     0,     0,     0,       0,      0,
                                                                                                 0,     278,   542,     298,    0,
                                                                                                 0,     -278, -542,     -297,   0,
                                                                                                 0,     0,      0,      0,      0);

        cv::Mat_<short> test_dy = (cv::Mat_<short>(image.rows,image.cols) <<                     0,     0,      0,      0,      0,
                                                                                                 0,     762,    30,     -764,   0,
                                                                                                 0,     762,    30,     -763,   0,
                                                                                                 0,     0,      0,      0,      0);


        //get the variables ready and set them

        edl->image = image;
        edl->gradientMagnitudes = cv::Mat::zeros(image.rows, image.cols, CV_8U);
        edl->dx = cv::Mat::zeros(image.rows, image.cols, CV_16S);
        edl->dy = cv::Mat::zeros(image.rows, image.cols, CV_16S);

        //call the method

        edl->calcGrad();

        // get the iterators

        cv::MatIterator_<uchar> itGradMag = edl->gradientMagnitudes.begin<uchar>();
        cv::MatIterator_<uchar> itTestGradMag = test_gradientMagnitudes.begin();
        cv::MatIterator_<short> itDx = edl->dx.begin<short>();
        cv::MatIterator_<short> itTestDx = test_dx.begin();
        cv::MatIterator_<short> itDy = edl->dy.begin<short>();
        cv::MatIterator_<short> itTestDy = test_dy.begin();

        // get an end

        cv::MatIterator_<uchar> itGradMag_end = edl->gradientMagnitudes.end<uchar>();

        // define pixels

        uchar pixGradMag;
        uchar pixTestGradMag;
        short pixDx;
        short pixTestDx;
        short pixDy;
        short pixTestDy;

        // run over the matrices and check each pixel

        for( ; itGradMag != itGradMag_end; ++itGradMag, ++itTestGradMag, ++itDx, ++itTestDx, ++itDy, ++itTestDy)
            {
                pixGradMag = *itGradMag;
                pixTestGradMag = *itTestGradMag;
                pixDx = *itDx;
                pixTestDx = *itTestDx;
                pixDy = *itDy;
                pixTestDy = *itTestDy;

                QVERIFY(pixGradMag == pixTestGradMag);
                QVERIFY(pixDx == pixTestDx);
                QVERIFY(pixDy == pixTestDy);
            }
    }

    void findAnchorsTest()
    {
        //Create an image

        cv::Mat_<uchar> image = (cv::Mat_<uchar>(4,5) <<    0,       0,       0,      0,       0,
                                                            1,      11,     255,     21,       0,
                                                            0,      12,     254,     22,       0,
                                                            0,       0,       0,      0,       0);
        //get the variables ready and set them

        edl->image = image;
        edl->gradientMagnitudes = cv::Mat::zeros(image.rows, image.cols, CV_8U);
        edl->dx = cv::Mat::zeros(image.rows, image.cols, CV_16S);
        edl->dy = cv::Mat::zeros(image.rows, image.cols, CV_16S);
        std::vector<cv::Point> anchors;

        //call the method

        edl->calcGrad();
        edl->findAnchors(anchors);

        // Points which should be found

        cv::Point a1 = cv::Point(1, 1);
        cv::Point a2 = cv::Point(3, 1);

        // check the found anchors

        QVERIFY(a1 == anchors[0]);
        QVERIFY(a2 == anchors[1]);
     }

    void getOrientationTest()
    {
        cv::Vec2s v1 = cv::Vec2s(2,4);
        QVERIFY(edl->getOrientation(v1) == VERTICAL);

        v1 = cv::Vec2s(4,2);
        QVERIFY(edl->getOrientation(v1) == HORIZONTAL);

        v1 = cv::Vec2s(3,7);
        QVERIFY(edl->getOrientation(v1) == VERTICAL);

        v1 = cv::Vec2s(7,3);
        QVERIFY(edl->getOrientation(v1) == HORIZONTAL);

        v1 = cv::Vec2s(5,5);
        QVERIFY(edl->getOrientation(v1) == HORIZONTAL);
    }

    void getNextPointTest()
    {
        // HORIZONTAL

        cv::Point left = cv::Point(-1, 0);
        cv::Point right = cv::Point(1, 0);

        // VERTICAL

        cv::Point up = cv::Point(0, -1);
        cv::Point down = cv::Point(0, 1);

        // start/end

        cv::Point currentPoint = cv::Point(1, 1);
        cv::Point *nextPoint;

        cv::Mat_<uchar> gradientMagnitudes = (cv::Mat_<uchar>(5,4) <<        1        ,2      ,3    ,4
                                                                            ,11       ,255    ,13   ,14
                                                                            ,21       ,22     ,80   ,15
                                                                            ,31       ,32     ,33   ,16
                                                                            ,41       ,42     ,43   ,17
                                                                            ,51       ,52     ,53   ,18); //walk over this
        edl->gradientMagnitudes = gradientMagnitudes;

        //simple walk

        nextPoint = edl->getNextPoint(currentPoint, right);
        QVERIFY(*nextPoint == cv::Point(2,2) && gradientMagnitudes(*nextPoint) == 80);

        nextPoint = edl->getNextPoint(currentPoint, left);
        QVERIFY(*nextPoint == cv::Point(0,2) && gradientMagnitudes(*nextPoint) == 21);

        nextPoint = edl->getNextPoint(currentPoint, up);
        QVERIFY(*nextPoint == cv::Point(2,0) && gradientMagnitudes(*nextPoint) == 3);

        nextPoint = edl->getNextPoint(currentPoint, down);
        QVERIFY(*nextPoint == cv::Point(2,2) && gradientMagnitudes(*nextPoint) == 80);

        //corner walk

        currentPoint = cv::Point(0, 3);

        nextPoint = edl->getNextPoint(currentPoint, right);
        QVERIFY(*nextPoint == cv::Point(1,4) && gradientMagnitudes(*nextPoint) == 42);

        nextPoint = edl->getNextPoint(currentPoint, left);
        QVERIFY(*nextPoint == cv::Point(0,3) && gradientMagnitudes(*nextPoint) == 31);

        nextPoint = edl->getNextPoint(currentPoint, up);
        QVERIFY(*nextPoint == cv::Point(1,2) && gradientMagnitudes(*nextPoint) == 22);

        nextPoint = edl->getNextPoint(currentPoint, down);
        QVERIFY(*nextPoint == cv::Point(1,4) && gradientMagnitudes(*nextPoint) == 42);
    }

    void walkFromAnchorTest()
    {
        //Create an image

        cv::Mat_<uchar> image = (cv::Mat_<uchar>(4,5) <<    0,       0,       0,      0,       0,
                                                            1,      11,     255,     21,       0,
                                                            0,      12,     254,     22,       0,
                                                            0,       0,       0,      0,       0);

        // set another minLineLength

        edl->minLineLength = 1;

        //get the variables ready and set them

        edl->image = image;
        edl->gradientMagnitudes = cv::Mat::zeros(image.rows, image.cols, CV_8U);
        edl->dx = cv::Mat::zeros(image.rows, image.cols, CV_16S);
        edl->dy = cv::Mat::zeros(image.rows, image.cols, CV_16S);
        std::vector<cv::Point> anchors;
        std::vector<std::list<cv::Point*>*> lineSegments;

        //call the previous methods

        edl->calcGrad();
        edl->findAnchors(anchors);

        // define stuff to work with

        cv::Point anchorPoint;
        std::list<cv::Point*>* lineSegment1;
        std::list<cv::Point*>* lineSegment2;

        //call walkFromAnchor 1

        anchorPoint = anchors[0];

        edl->walkFromAnchor(anchorPoint, lineSegments);

        lineSegment1 = lineSegments.at(0);
        lineSegment2 = lineSegments.at(1);
        QCOMPARE(*lineSegment1->front(), cv::Point(1,1));
        QCOMPARE(*lineSegment2->front(), cv::Point(1,2));
    }

    void getAngleBetweenVectorsTest()
    {
        cv::Vec2s v1 = cv::Vec2s(2,4);
        cv::Vec2s v2 = cv::Vec2s(2,5);
        double angle1 = calcAngle(v1,v2);
        double angle2 = fabs(edl->getAngleBetweenVectors(v1, v2));
        QVERIFY((angle2 - angle1) > -0.01 && (angle2 - angle1) <= 0.01 );

        v1 = cv::Vec2s(3,7);
        v2 = cv::Vec2s(7,3);
        angle1 = calcAngle(v1,v2);
        angle2 = fabs(edl->getAngleBetweenVectors(v1, v2));
        QVERIFY((angle2 - angle1) > -0.01 && (angle2 - angle1) <= 0.01 );

        v1 = cv::Vec2s(1,4);
        v2 = cv::Vec2s(1,7);
        angle1 = calcAngle(v1,v2);
        angle2 = fabs(edl->getAngleBetweenVectors(v1, v2));
        QVERIFY((angle2 - angle1) > -0.01 && (angle2 - angle1) <= 0.01 );
    }

    void isOutOfBoundsTest()
    {
        edl->gradientMagnitudes = cv::Mat::zeros(2,3,CV_8U);

        cv::Point point(-1, 0);
        QVERIFY(true == edl->isOutOfBounds(point));
        QVERIFY(true == edl->isOutOfBounds(-1, 0));

        point = cv::Point(0, 0);
        QVERIFY(false == edl->isOutOfBounds(point));
        QVERIFY(false == edl->isOutOfBounds(0, 0));

        point = cv::Point(2, 2);
        QVERIFY(false == edl->isOutOfBounds(point));
        QVERIFY(false == edl->isOutOfBounds(2,2 ));

        point = cv::Point(2, 3);
        QVERIFY(true == edl->isOutOfBounds(point));
        QVERIFY(true == edl->isOutOfBounds(2, 3));

        point = cv::Point(3, 2);
        QVERIFY(false == edl->isOutOfBounds(point));
        QVERIFY(false == edl->isOutOfBounds(3, 2));

        point= cv::Point(1, -1);
        QVERIFY(true == edl->isOutOfBounds(point));
        QVERIFY(true == edl->isOutOfBounds(1, -1));
    }

    void getSobelVectorTest()
    {
        // define matrices

        cv::Mat_<short> dx = (cv::Mat_<short>(4,5) <<                 0,      0,    0,        0,     0,
                                                                     01,     11,    21,      31,    41,
                                                                     02,     21,    22,      32,    42,
                                                                     03,     31,    32,      33,    43);

        cv::Mat_<short> dy = (cv::Mat_<short>(4,5) <<                03,     31,    32,      33,     43,
                                                                     02,     21,    22,      32,     42,
                                                                     01,     11,    12,      31,     41,
                                                                      0,     0,      0,      0,      0);

        // define stuff to work with

        cv::Point point;
        cv::Vec2s test_vector;

        // set the parameters

        edl->dx = dx;
        edl->dy = dy;

        // do the testing

        point = cv::Point(1, 1);
        test_vector = cv::Vec2s(11, 21);


        QVERIFY(*(edl->getSobelVector(point)) == test_vector);
        QVERIFY(*(edl->getSobelVector(1, 1)) == test_vector);

        point = cv::Point(1, 2);
        test_vector = cv::Vec2s(21, 11);

        QVERIFY(*(edl->getSobelVector(point)) == test_vector);
        QVERIFY(*(edl->getSobelVector(2, 1)) == test_vector);

        point = cv::Point(1, 3);
        test_vector = cv::Vec2s(31, 0);

        QVERIFY(*(edl->getSobelVector(point)) == test_vector);
        QVERIFY(*(edl->getSobelVector(3, 1)) == test_vector);

        point = cv::Point(3, 1);
        test_vector = cv::Vec2s(31, 32);

        QVERIFY(*(edl->getSobelVector(point)) == test_vector);
        QVERIFY(*(edl->getSobelVector(1, 3)) == test_vector);

        point = cv::Point(3, 3);
        test_vector = cv::Vec2s(33, 0);

        QVERIFY(*(edl->getSobelVector(point)) == test_vector);
        QVERIFY(*(edl->getSobelVector(3, 3)) == test_vector);


    }

    void cleanupTestCase()
    {
        delete edl;
    }

private:
    EDL2* edl;

    double calcAngle(cv::Vec2s &v1, cv::Vec2s &v2)
    {
        return std::acos(v1.dot(v2) / ((std::sqrt(v1[0]*v1[0]+v1[1]*v1[1])) * (std::sqrt(v2[0]*v2[0]+v2[1]*v2[1]))));
    }
};

#endif // EDLTEST_H
