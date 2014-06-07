#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

ObjectDetectionAlgorithm::ObjectDetectionAlgorithm(const std::vector<Model>& databaseModels)
    : databaseModels(databaseModels)
{
}

} // namespace formseher
