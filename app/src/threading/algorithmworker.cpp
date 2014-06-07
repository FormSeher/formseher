#include "threading/algorithmworker.h"

#include "linedetection/linedetectionalgorithm.h"
#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

AlgorithmWorker::AlgorithmWorker(LineDetectionAlgorithm* lineAlgorithm, ObjectDetectionAlgorithm *objectAlgorithm, cv::InputArray image, std::vector<Line> presetLines, QObject *parent)
    : QThread(parent),
      lineAlgorithm(lineAlgorithm),
      objectAlgorithm(objectAlgorithm)
{
    this->image = image.getMat();

    if(!presetLines.empty())
        this->result = presetLines;
}

AlgorithmWorker::~AlgorithmWorker()
{
}

void AlgorithmWorker::run()
{
    if(lineAlgorithm)
        result = lineAlgorithm->calculate(image);
    if(objectAlgorithm)
        objectAlgorithm->calculate(result);
    emit resultReady();
}

std::vector<Line> AlgorithmWorker::getResult()
{
    return result;
}

} // namespace formseher
