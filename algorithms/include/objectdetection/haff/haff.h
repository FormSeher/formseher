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
    /**
     * @brief Haff constructor.
     *
     * Initializes Haff algorithm by given ( or default) parameters.
     *
     * @param numberOfBestHypotheses Maximal number of hypotheses kept from one hypothesis creation to the other.
     * @param numberOfDetectedObjects Maximal number of objects to detect.
     * @param minimalObjectRating Minimal object rating allowed.
     * @param coverageWeight Weight factor for coverage rating.
     * @param angleWeight Weight factor for angle rating.
     * @param positionWeight Weight factor of position rating.
     */
    Haff(int numberOfBestHypotheses = 10, int numberOfDetectedObjects = 10,
         double minimalObjectRating = 60.0, double coverageWeight = 1.0 / 3.0, double angleWeight = 1.0 / 3.0,
         double positionWeight = 1.0 / 3.0);

    /*! @copydoc ObjectDetection::calculate()
     */
    std::vector<Object> calculate(std::vector<Line> detectedLines);

private:
    int numberOfBestHypotheses;
    int numberOfDetectedObjects;
    double minimalObjectRating;
    double coverageWeight;
    double angleWeight;
    double positionWeight;

    /**
     * @brief Inserts object into detectedObjects only if its position does not interfere with a different object.
     * @param detectedObjects Vector of already detected objects.
     * @param object The object to be inserted into detectedObjects
     */
    void suppressedInsertion(std::vector<Object> &detectedObjects, Object &object);
};
}   //  namespace formseher

#endif // HAFF_H
