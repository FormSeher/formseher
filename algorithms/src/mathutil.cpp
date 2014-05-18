#include "mathutil.h"

namespace formseher
{

namespace math
{

float sqrtFast(float num)
{
    unsigned int i = *(unsigned int*) &num;

    i  += 127 << 23;

    i >>= 1;
    return *(float*) &i;
}

} // namespace math
} // namespace formseher
