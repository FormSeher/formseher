#include "algorithm.h"

#include "line.h"

Algorithm::Algorithm()
    : configChanged(true)
{
}

bool Algorithm::startThreaded()
{
    return true;
}

void Algorithm::run()
{
    // TODO: Stub implementation only. Improve wait condition!
    while(true)
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

void Algorithm::setInput(std::string filePath)
{
    inputFilePath = filePath;
}

void Algorithm::changedConfig()
{
    configChanged = true;
}
