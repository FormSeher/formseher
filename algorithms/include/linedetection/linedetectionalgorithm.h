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

#ifndef FS_LINEDETECTIONALGORITHM_H
#define FS_LINEDETECTIONALGORITHM_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <opencv2/core/core.hpp>

namespace formseher
{

class Line;

/**
 * @brief The abstract Algorithm class used to implement line detection algorithms.
 *
 * Derive from this class to create a custom line detection algorithm.
 */
class LineDetectionAlgorithm
{
public:
    /**
     * @brief Standard ctor.
     */
    LineDetectionAlgorithm();

    /**
     * @brief Standard dtor.
     */
    virtual ~LineDetectionAlgorithm();

    /**
     * @brief Run the algorithm once.
     *
     * This method is called to execute the algorithm one time. You have to implement
     * it when you create a custom line detection algorithm. This method should update
     * the result vector.
     */
    virtual std::vector<Line> calculate(cv::InputArray image) = 0;
};

} // namespace formseher

#endif // FS_LINEDETECTIONALGORITHM_H
