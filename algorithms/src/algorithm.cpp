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
    // TODO: Stub implementation only. Improve wait condition!
    while(!stopThread)
    {
        if(configChanged)
        {
            calculate();
        }
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
