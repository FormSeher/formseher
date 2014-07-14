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

#ifndef FS_MODEL_H
#define FS_MODEL_H

#include <opencv2/core/core.hpp>
#include <string.h>
#include "line.h"

namespace formseher {

class Model
{

public:
    /**
     * @brief Model standard constructor.
     */
    Model();

    /**
     * @brief Model copy constructor.
     *
     * Makes a deep copy of rhs model.
     *
     * @param model the model copied.
     */
    Model(const Model& model);

    /**
     * @brief Model destructor.
     */
    virtual ~Model();

    /**
     * @brief Assignemtn operator.
     *
     * Makes a deep copy of the rhs model.
     *
     * @param rhs Right hand operand.
     * @return Reference to this.
     */
    Model& operator=(const Model& rhs);

    /**
     * @brief Add a line to the model.
     *
     * This also updates bounding box of model.
     *
     * @param line The line which is added to the model.
     */
    void addLine(const Line line);

    /**
     * @brief Get all lines added to the model.
     * @return Vector of model's lines.s
     */
    const std::vector<const Line*>& getLines() const;

    /**
     * @brief Get bounding box which contains the model.
     * @return Bounding box as a OpenCV Rect.
     */
    cv::Rect getBoundingBox() const;

    /**
     * @brief Set name of the model.
     * @param name The new model name.
     */
    void setName(std::string name);

    /**
     * @brief Get the name of the model.
     * @return The model name.
     */
    std::string getName() const;

    /**
     * @brief Deserializes Object form string.
     *
     * Take a serialied representation of an Object and initialize this
     * from it. Previously added lines are preserved!
     * Form of the serialized string: @see Object::toString()
     *
     * @param string String of an serialized Object.
     */
    void fromString(const std::string &string);

    /**
     * @brief Serializes Object to string.
     *
     * Following format is used:
     * <name>:<line1>;<line2>;<line3>;
     *
     * Each <lineN> is a serialized Line with following format:
     * <x of start>,<y of start>,<x of end>,<y of end>
     *
     * Example:
     * Fancy object:1,2,3,4;11,22,33,44;
     *
     * @return Serialized Object as string.
     */
    std::string toString();

private:
    /**
     * @brief Make a deep copy of right hand side model.
     * @param rhs Model to be copied.
     */
    void copy(const Model& rhs);

    void updateBoundingBox(const cv::Point2i& point);
    cv::Point2i boundingBoxCorners[2];

    std::string name;

protected:
    std::vector<const Line*> lines;
};

}   // formseher

#endif // FS_MODEL_H
