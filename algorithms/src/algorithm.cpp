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

std::vector<Line*>& Algorithm::getResult()
{
    return result;
}

double Algorithm::getCoputationTime()
{
    return computationTime;
}

void Algorithm::setInput(std::string filePath)
{
    inputFilePath = filePath;
}

void Algorithm::changedConfig()
{
    configChanged = true;
}

void Algorithm::setComputationTime(double computationTime)
{
    this->computationTime = computationTime;
}
