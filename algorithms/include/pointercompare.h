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

#ifndef FS_POINTERCOMPARE_H
#define FS_POINTERCOMPARE_H

namespace formseher
{

/**
 * @brief Class which provides less operator for pointer types.
 */
template<class T>
class PointerCompare
{
public:
    /**
     * @brief Call operator which compares two operands of type T*.
     *
     * Comparision is done by ereferencing the pointers and calling the less-operator.
     *
     * @param lhs Left hand side operand.
     * @param rhs Right hand side operand.
     * @return True if lhs is less than rhs, false otherwise.
     */
    bool operator()(const T* const& lhs, const T* const& rhs) const
    {
        return (*lhs) < (*rhs);
    }
};

} // namespace formseher

#endif // FS_POINTERCOMPARE_H
