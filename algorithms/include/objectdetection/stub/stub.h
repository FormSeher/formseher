#ifndef STUB_H
#define STUB_H

#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

class Stub : public ObjectDetectionAlgorithm
{
public:
    Stub();

    std::vector<Object> calculate(std::vector<Line>);
};

} // namespace formseher

#endif // STUB_H
