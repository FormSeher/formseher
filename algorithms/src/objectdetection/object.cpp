#include "objectdetection/object.h"

namespace formseher
{

Object::Object()
    : rating(0.0f)
{
}

Object::Object(const Object &object)
    : Model(object)
{
    rating = object.rating;
}

void Object::setRating(float rating)
{
    this->rating = rating;
}

float Object::getRating()
{
    return rating;
}

void Object::clearLines(){
    lines.clear();
}

} // namespace formseher
