/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

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
