#include "threading/algorithmworker.h"

#include "linedetection/linedetectionalgorithm.h"
#include "objectdetection/objectdetectionalgorithm.h"

#include "line.h"
#include "objectdetection/object.h"

namespace formseher
{

AlgorithmWorker::AlgorithmWorker(LineDetectionAlgorithm* lineAlgorithm, ObjectDetectionAlgorithm *objectAlgorithm, cv::InputArray image, std::vector<Line> presetLines, QObject *parent)
    : QThread(parent),
      lineAlgorithm(lineAlgorithm),
      objectAlgorithm(objectAlgorithm)
{
    this->image = image.getMat();

    if(!presetLines.empty())
        this->result.first = presetLines;
}

AlgorithmWorker::AlgorithmWorker(ObjectDetectionAlgorithm* algorithm, cv::InputArray image, QObject *parent)
    : QThread(parent),
      algorithm(algorithm)
{
    this->image = image.getMat();
}


AlgorithmWorker::~AlgorithmWorker()
{
}

void AlgorithmWorker::run()
{
    if(lineAlgorithm)
        result.first = lineAlgorithm->calculate(image);
    if(objectAlgorithm)
        result.second = objectAlgorithm->calculate(result.first);
    emit resultReady();
}

algorithmworker_result AlgorithmWorker::getResult()
{
    return result;
}

} // namespace formseher
