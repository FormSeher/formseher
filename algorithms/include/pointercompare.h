#ifndef POINTERCOMPARE_H
#define POINTERCOMPARE_H

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

#endif // POINTERCOMPARE_H
