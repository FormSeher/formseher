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

#ifndef LINEUTILS_H
#define LINEUTILS_H

#include "line.h"

namespace formseher {

class LineUtils
{
public:
    LineUtils();

    /**
     * @brief combineLines Combines lines in the given vector that represent logically the same line.
     * @param lineList Lines from linedetection algorithm.
     * @return Vector that contains just the combined lines.
     */
    static void combineLines(std::vector<Line>& lineList);
};

} // namesspace formseher

#endif // LINEUTILS_H
