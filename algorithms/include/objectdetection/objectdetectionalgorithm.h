#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "object.h"
#include "line.h"

namespace formseher {

class ObjectDetectionAlgorithm
{
public:
    ObjectDetectionAlgorithm();

    virtual std::vector<Object*> calculate(std::vector<Line>) = 0;

};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H