#ifndef STUB_H
#define STUB_H

#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

/**
 * @brief Stub implementation of ObjectDetectionAlgorithm which just returns the database models.
 *
 * This "algorithm" is for test purpose only.
 */
class Stub : public ObjectDetectionAlgorithm
{
public:
    /**
     * @brief Stub standard constructor.
     */
    Stub();

    /**
     * @brief Returns the models set by ObjectDetectionAlgorithm::setModels().
     * @return The models converted to objects.
     */
    std::vector<Object> calculate(std::vector<Line>);
};

} // namespace formseher

#endif // STUB_H
