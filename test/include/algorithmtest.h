#ifndef ALGORITHMTEST_H
#define ALGORITHMTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "algorithm.h"


class AlgorithmStub : public Algorithm
{
public:
    ~AlgorithmStub() {}
    void calculate()
    {
    }
};

class AlgorithmTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
//        algorithm = new AlgorithmStub();
    }

    void startThreadedTest()
    {
//        QVERIFY(true == algorithm->startThreaded());
    }

    void stopThreadedTest()
    {
//        algorithm->stopThreaded();
    }

    void cleanupTestCase()
    {
//        delete algorithm;
    }

private:
   AlgorithmStub* algorithm;
};


#endif // ALGORITHMTEST_H
