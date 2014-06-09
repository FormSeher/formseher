#include "objectdetection/stub/stub.h"

namespace formseher
{

Stub::Stub()
{
}

std::vector<Object> Stub::calculate(std::vector<Line>)
{
    std::vector<Object> objects;

    for(auto model : databaseModels)
    {
        Object object;
        object.setName(model.getName());

        for(auto line : model.getLines())
        {
            object.addLine(*line);
        }
        objects.push_back(object);
    }

    return objects;
}

} // namespace formseher
