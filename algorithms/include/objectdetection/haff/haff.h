#ifndef HAFF_H
#define HAFF_H

#include "objectdetection/objectdetectionalgorithm.h"
#include "line.h"
#include "objectdetection/haff/haffdatabase.h"

namespace formseher
{

class Model;

class Haff : public ObjectDetectionAlgorithm
{

public:
    Haff(const std::vector<Model>& databaseModels);

    std::vector<Object> calculate(std::vector<Line> detectedLines);

private:
};

}   //  namespace formseher

#endif // HAFF_H
