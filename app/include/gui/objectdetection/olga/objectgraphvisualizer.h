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

#ifndef FS_OBJECTGRAPHVISUALIZER_H
#define FS_OBJECTGRAPHVISUALIZER_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class ObjectGraph;

class ObjectGraphVisualizer
{
public:
    /**
     * @brief ObjectGraphVisualizer standard constructor.
     */
    ObjectGraphVisualizer();

    /**
     * @brief Draws given graph to given matrix.
     * @param graph ObjectGraph to be drawn.
     * @param matrix Matrix graph is drawn onto.
     */
    static void drawGraphOnMatrix(const ObjectGraph* graph, cv::OutputArray matrix);
};

} // namespace formseher
#endif // FS_OBJECTGRAPHVISUALIZER_H
