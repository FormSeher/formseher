#include "objectdetection/haff/haffdatabase.h"

#include <fstream>

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

bool HaffDatabase::load()
{
    std::ifstream file;
    file.open(filePath);

    if(!file.is_open())
        return false;

    std::string line;
    Object* object;

    while(getline(file, line))
    {
        object = new Object();
        object->fromString(line);
        objects.push_back(object);
    }

    return true;
}

const std::vector<const Object *> &HaffDatabase::getObjects() const
{
    return objects;
}

} // namespace formseher
