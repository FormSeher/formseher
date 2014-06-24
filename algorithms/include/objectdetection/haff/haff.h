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
    Haff(int numberOfBestHypotheses = 10, int numberOfDetectedObjects = 10,
         double minimalObjectRating = 60.0, double coverageWeight = 1.0 / 3.0, double angleWeight = 1.0 / 3.0,
         double positionWeight = 1.0 / 3.0);

    std::vector<Object> calculate(std::vector<Line> detectedLines);

private:
    int numberOfBestHypotheses;
    int numberOfDetectedObjects;
    double minimalObjectRating;
    double coverageWeight;
    double angleWeight;
    double positionWeight;
};
}   //  namespace formseher

#endif // HAFF_H
