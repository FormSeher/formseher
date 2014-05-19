#ifndef POINTERCOMPARE_H
#define POINTERCOMPARE_H

template<class T>
class PointerCompare
{
public:
    bool operator()(const T* const& lhs, const T* const& rhs) const
    {
        return (*lhs) < (*rhs);
    }
};

#endif // POINTERCOMPARE_H
