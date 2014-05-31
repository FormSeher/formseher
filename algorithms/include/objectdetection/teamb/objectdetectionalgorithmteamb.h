#ifndef OBJECTDETECTIONALGORITHMTEAMB_H
#define OBJECTDETECTIONALGORITHMTEAMB_H

#include "objectdetection/objectdetectionalgorithm.h"
#include "line.h"
#include "objectdetection/model.h"
#include "objectdetection/object.h"

namespace formseher
{

class ObjectDetectionAlgorithmTeamB : public ObjectDetectionAlgorithm
{

public:
    ObjectDetectionAlgorithmTeamB();

    std::vector<Object> calculate(std::vector<Line> lines) = 0;

private:
    int databaseSize;
    std::vector<Model> databaseObjects;

    void getAllDatabaseObjects();
    void rateObject(Object& consideredObject, Line lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine);
    void getBestRatedObjects(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects);

};   //  namespace formseher
}
#endif // OBJECTDETECTIONALGORITHMTEAMB_H
