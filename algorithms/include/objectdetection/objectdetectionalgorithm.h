#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "objectdetection/object.h"
#include "line.h"

namespace formseher {

class Model;

class ObjectDetectionAlgorithm
{
public:
    /**
     * @brief ObjectDetectionAlgorithm standard constructor.
     */
    ObjectDetectionAlgorithm();

    /**
     * @brief ObjectDetectionAlgorithm destructor.
     */
    virtual ~ObjectDetectionAlgorithm();

    /**
     * @brief Runs the object detection algorithm on given lines.
     * @param lines Vector of lines (e.g. result of a LineDetectionAlgorithm).
     * @return Vector of objects detected in lines.
     */
    virtual std::vector<Object> calculate(std::vector<Line> lines) = 0;

    /**
     * @brief Set the models which can be detected by the algorithm.
     * @param databaseModels Vector of Models.
     */
    void setModels(const std::vector<Model>& databaseModels);

protected:
    std::vector<Model> databaseModels;
};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
