#include "objectdetection/haff/haffdatabase.h"

namespace formseher {

HaffDatabase::HaffDatabase(std::string filePath)
    : filePath(filePath)
{
}

HaffDatabase::~HaffDatabase()
{
    for(auto object : objects)
        delete object;
}

void HaffDatabase::load()
{
    // load objects from file
}

const std::vector<const Object *> &HaffDatabase::getObjects() const
{
    return objects;
}

} // namespace formseher
