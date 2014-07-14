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

#include "objectdetection/haff/haffdatabase.h"

#include <fstream>

namespace formseher {

HaffDatabase::HaffDatabase(std::string filePath)
    : filePath(filePath)
{
}

HaffDatabase::~HaffDatabase()
{
    for(auto object : objects)
        delete object;
}

bool HaffDatabase::load()
{
    std::ifstream file;
    file.open(filePath);

    if(!file.is_open())
        return false;

    std::string line;
    Object* object;

    while(getline(file, line))
    {
        object = new Object();
        object->fromString(line);
        objects.push_back(object);
    }

    file.close();

    return true;
}

const std::vector<const Object *> &HaffDatabase::getObjects() const
{
    return objects;
}

} // namespace formseher
