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

#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "objectdetection/object.h"
#include "line.h"

namespace formseher {

class Model;

class ObjectDetectionAlgorithm
{
public:
    /**
     * @brief ObjectDetectionAlgorithm standard constructor.
     */
    ObjectDetectionAlgorithm();

    /**
     * @brief ObjectDetectionAlgorithm destructor.
     */
    virtual ~ObjectDetectionAlgorithm();

    /**
     * @brief Runs the object detection algorithm on given lines.
     * @param lines Vector of lines (e.g. result of a LineDetectionAlgorithm).
     * @return Vector of objects detected in lines.
     */
    virtual std::vector<Object> calculate(std::vector<Line> lines) = 0;

    /**
     * @brief Set the models which can be detected by the algorithm.
     * @param databaseModels Vector of Models.
     */
    void setModels(const std::vector<Model>& databaseModels);

protected:
    std::vector<Model> databaseModels;
};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
