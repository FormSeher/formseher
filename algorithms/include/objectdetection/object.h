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

#ifndef FS_OBJECT_H
#define FS_OBJECT_H

#include "objectdetection/model.h"

namespace formseher
{

class Object : public Model
{
public:
    /**
     * @brief Object standard constructor
     */
    Object();

    /**
     * @brief Object copy constructor
     * @param object Object that is copied.
     */
    Object(const Object& object);

    /**
     * @brief Sets the rating of the Object.
     * @param rating The rating.
     */
    void setRating(float rating);

    /**
     * @brief Get the rating of the Object.
     * @return The rating.
     */
    float getRating();

    /**
     * @brief Clears the list of lines.
     */
    void clearLines();

private:
    float rating;
};

} // namespace formseher

#endif // FS_OBJECT_H
