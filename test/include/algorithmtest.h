#ifndef ALGORITHMTEST_H
#define ALGORITHMTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "line.h"

// brute force everything public (don't do this at home kids!)
#undef private
#undef protected
#define private public
#define protected public

#include "algorithm.h"

// Restore visibilities
#undef private
#undef protected
#define protected protected
#define private private


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
        algorithm = new AlgorithmStub();
    }

    // Test if ctor behaves correctly
    void initializerTest()
    {
        QVERIFY(true == algorithm->configChanged);
        QVERIFY(0 == algorithm->thread);
        QVERIFY(false == algorithm->stopThread);
    }

    void startThreadedTest()
    {
        QVERIFY(true == algorithm->startThreaded());
        QVERIFY(false == algorithm->stopThread);
        QVERIFY(0 != algorithm->thread);

        QVERIFY(false == algorithm->startThreaded());

        algorithm->stopThreaded();
    }

    void stopThreadedTest()
    {
        algorithm->startThreaded();

        algorithm->stopThreaded();
        QVERIFY(true == algorithm->stopThread);
        QVERIFY(0 == algorithm->thread);
    }

    void getComputationTimeTest()
    {
        algorithm->computationTime = 13.37;
        QVERIFY(13.37 == algorithm->getComputationTime());
    }

    void setInputTest()
    {
        algorithm->configChanged = false;
        algorithm->setInput("this/is/input.file");
        QVERIFY("this/is/input.file" == algorithm->inputFilePath);
        QVERIFY(true == algorithm->configChanged);
    }

    void setConfigChangedTest()
    {
        algorithm->configChanged = false;

        algorithm->setConfigChanged(true);
        QVERIFY(true == algorithm->configChanged);
    }

    void setResultTest()
    {
        // Set a result
        std::vector<Line*>* result = new std::vector<Line*>;
        result->push_back(new Line());
        result->push_back(new Line());

        algorithm->setResult(result, 12.5);

        QVERIFY(result == algorithm->result);
        QVERIFY(12.5 == algorithm->computationTime);

        // Set another result
        algorithm->setResult(0, 0.0);

        QVERIFY(0 == algorithm->result);
    }

    void getResultTest()
    {
        std::vector<Line*> result;
        Line* line = new Line();
        result.push_back(line);

        algorithm->result = &result;

        std::vector<Line*>* algoResult = algorithm->getResult();

        QVERIFY(&result != algoResult);
        QVERIFY(result.at(0) != algoResult->at(0));

        algorithm->result = 0;
        delete line;
    }

    void cleanupTestCase()
    {
        delete algorithm;
    }

private:
   AlgorithmStub* algorithm;
};


#endif // ALGORITHMTEST_H
