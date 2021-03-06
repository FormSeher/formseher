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

#include "objectdetection/stub/stub.h"

namespace formseher
{

Stub::Stub()
{
}

std::vector<Object> Stub::calculate(std::vector<Line>)
{
    std::vector<Object> objects;

    for(auto model : databaseModels)
    {
        Object object;
        object.setName(model.getName());

        for(auto line : model.getLines())
        {
            object.addLine(*line);
        }
        objects.push_back(object);
    }

    return objects;
}

} // namespace formseher
