#ifndef HAFF_H
#define HAFF_H

#include "objectdetection/objectdetectionalgorithm.h"
#include "line.h"
#include "objectdetection/haff/haffdatabase.h"

namespace formseher
{

class Haff : public ObjectDetectionAlgorithm
{

public:
    Haff(const HaffDatabase& database);

    std::vector<Object> calculate(std::vector<Line> detectedLines);

private:
    const HaffDatabase& database;
};

}   //  namespace formseher

#endif // HAFF_H
