#include "algorithm.h"

#include "line.h"

#include <iostream>

Algorithm::Algorithm()
    : configChanged(true),
      thread(0),
      stopThread(false)
{
}

Algorithm::~Algorithm()
{
    stopThreaded();
}

bool Algorithm::startThreaded()
{
    if(thread != 0)
    {
        return false;
    }

    stopThread = false;
    thread = new std::thread(&Algorithm::run, this);
    return true;
}

void Algorithm::stopThreaded()
{
    if(thread == 0)
    {
        return;
    }

    stopThread = true;
    thread->join();
    delete thread;
    thread = 0;
}

void Algorithm::run()
{
    std::unique_lock<std::mutex> lock(configConditionMutex);

    while(!stopThread)
    {
        configChangedMutex.lock();
        if(!configChanged) {
            configChangedMutex.unlock();
            configChangedCondition.wait(lock);
        }
        configChangedMutex.unlock();

        calculate();
    }
}

std::vector<Line*>* Algorithm::getResult()
{
    resultMutex.lock();

    // Create a copy of the result
    std::vector<Line*>* resultCopy = new std::vector<Line*>;
    for(auto line : *result)
    {
        resultCopy->push_back(new Line(*line));
    }

    resultMutex.unlock();

    return resultCopy;
}

double Algorithm::getCoputationTime()
{
    return computationTime;
}

void Algorithm::setInput(std::string filePath)
{
    inputFilePath = filePath;
}

void Algorithm::setConfigChanged(bool configChanged)
{
    configChangedMutex.lock();
    this->configChanged = configChanged;
    configChangedMutex.unlock();
}

void Algorithm::setResult(std::vector<Line*>* result, double computationTime)
{
    resultMutex.lock();

    // Delete the old result
    for(auto iterator : *this->result)
    {
        delete iterator;
    }
    delete this->result;

    this->result = result;
    this->computationTime = computationTime;

    resultMutex.unlock();
}
