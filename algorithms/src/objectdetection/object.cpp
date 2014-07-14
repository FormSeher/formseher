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

#include "objectdetection/object.h"

namespace formseher
{

Object::Object()
    : rating(0.0f)
{
}

Object::Object(const Object &object)
    : Model(object)
{
    rating = object.rating;
}

void Object::setRating(float rating)
{
    this->rating = rating;
}

float Object::getRating()
{
    return rating;
}

void Object::clearLines(){
    lines.clear();
}

} // namespace formseher
