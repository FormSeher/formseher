#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

ObjectDetectionAlgorithm::ObjectDetectionAlgorithm()
{
}

ObjectDetectionAlgorithm::~ObjectDetectionAlgorithm()
{
}

void ObjectDetectionAlgorithm::setModels(const std::vector<Model> &databaseModels)
{
    this->databaseModels = databaseModels;
}

} // namespace formseher
