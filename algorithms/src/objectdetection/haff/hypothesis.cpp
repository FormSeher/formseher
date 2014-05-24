#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

const double Hypothesis::angleFactor = 1.0;
const double Hypothesis::coverFactor = 1.0;
const double Hypothesis::scaleFactor = 1.0;

void Hypothesis::calculateRating()
{

}

double Hypothesis::getRating() const
{
    return 0.0;
}

bool Hypothesis::containsLine(const Line *line) const
{
    return false;
}

} // namespace formseher
