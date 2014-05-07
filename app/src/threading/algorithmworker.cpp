#include "threading/algorithmworker.h"

AlgorithmWorker::AlgorithmWorker(Algorithm* algorithm, cv::InputArray image, QObject *parent)
    : QThread(parent),
      algorithm(algorithm)
{
    this->image = image.getMat();
}

AlgorithmWorker::~AlgorithmWorker()
{
    delete algorithm;
}

void AlgorithmWorker::run()
{
    result = algorithm->calculate(image);
    emit resultReady();
}

std::vector<Line> AlgorithmWorker::getResult()
{
    return result;
}
