#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "objectdetection/object.h"
#include "line.h"

namespace formseher {

class Model;

class ObjectDetectionAlgorithm
{
public:
    ObjectDetectionAlgorithm(const std::vector<Model>& databaseModels);
    virtual ~ObjectDetectionAlgorithm();

    virtual std::vector<Object> calculate(std::vector<Line>) = 0;

protected:
    std::vector<Model> databaseModels;
};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
