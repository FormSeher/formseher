#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "objectdetection/object.h"
#include "line.h"

namespace formseher {

class Model;

class ObjectDetectionAlgorithm
{
public:
    ObjectDetectionAlgorithm();
    virtual ~ObjectDetectionAlgorithm();

    virtual std::vector<Object> calculate(std::vector<Line>) = 0;

    void setModels(const std::vector<Model>& databaseModels);

protected:
    std::vector<Model> databaseModels;
};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
