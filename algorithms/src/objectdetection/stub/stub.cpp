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
        Object o;
        o.setName(model.getName());

        for(auto line : model.getLines())
        {
            o.addLine(*line);
        }
    }

    return objects;
}

} // namespace formseher
