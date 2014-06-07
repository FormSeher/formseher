#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

ObjectDetectionAlgorithm::ObjectDetectionAlgorithm(const std::vector<Model>& databaseModels)
    : databaseModels(databaseModels)
{
}

ObjectDetectionAlgorithm::~ObjectDetectionAlgorithm()
{
}

} // namespace formseher
