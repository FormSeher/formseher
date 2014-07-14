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

#ifndef STUB_H
#define STUB_H

#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

/**
 * @brief Stub implementation of ObjectDetectionAlgorithm which just returns the database models.
 *
 * This "algorithm" is for test purpose only.
 */
class Stub : public ObjectDetectionAlgorithm
{
public:
    /**
     * @brief Stub standard constructor.
     */
    Stub();

    /**
     * @brief Returns the models set by ObjectDetectionAlgorithm::setModels().
     * @return The models converted to objects.
     */
    std::vector<Object> calculate(std::vector<Line>);
};

} // namespace formseher

#endif // STUB_H
