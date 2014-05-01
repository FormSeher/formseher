#include "algorithmworker.h"

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
    std::vector<Line> result = algorithm->calculate(image);
    emit resultReady(result);
}
