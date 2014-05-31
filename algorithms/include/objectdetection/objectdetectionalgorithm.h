#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "objectdetection/model.h"
#include "line.h"

namespace formseher {

class ObjectDetectionAlgorithm
{
public:
    ObjectDetectionAlgorithm();

    virtual std::vector<Model*> calculate(std::vector<Line>) = 0;

};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
