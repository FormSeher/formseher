#include "objectdetection/object.h"

namespace formseher
{

Object::Object()
    : rating(0.0f)
{
}

void Object::setRating(float rating)
{
    this->rating = rating;
}

float Object::getRating()
{
    return rating;
}

} // namespace formseher
