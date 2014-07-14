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

#ifndef FS_HAFFDATABASE_H
#define FS_HAFFDATABASE_H

#include <vector>
#include <string>

#include "objectdetection/object.h"

namespace formseher {

class HaffDatabase
{
public:
    /**
     * @brief Ceate a new instance of a HaffDatabase.
     * @param filePath The file where the database is stored.
     */
    HaffDatabase(std::string filePath);

    /**
     * @brief Destructor. WARNING: All Object-pointers retrieved from this
     * Database become invalid!
     */
    ~HaffDatabase();

    /**
     * @brief Loads the objects stored in the database.
     */
    bool load();

    /**
     * @brief Get the objects previously loaded by HaffDatabase::load().
     * @return Vector of the Objects
     */
    const std::vector<const Object*>& getObjects() const;

private:
    // Path to the database file
    std::string filePath;

    // Populated by Objects retrieved from load().
    std::vector<const Object*> objects;
};

} // namespace formseher

#endif // FS_HAFFDATABASE_H
