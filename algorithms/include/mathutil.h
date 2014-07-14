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

#ifndef FS_MATHUTIL_H
#define FS_MATHUTIL_H

namespace formseher
{

namespace math
{

// Constants
const double m_pi = 3.14159265358979323846;

/**
 * @brief A fast implementation of the square root function.
 * @param num Number of which square root is taken.
 * @return The square root of num.
 */
float sqrtFast(float num);

} // namespace math
} // namespace formseher
#endif // FS_MATH_H
