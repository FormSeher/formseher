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

    virtual std::vector<Object*> calculate(std::vector<Line> lines) = 0;

private:
    int databaseSize;
    std::vector<Model> databaseObjects;

    void getAllDatabaseObjects();
    void getFirstRating(int& rating, Line firstLine, Line secondLine, Object databaseObject);
    void rateObject(Object consideredObject, Line lineToCheck, Model databaseObject, int currentLineNumber);
}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHMTEAMB_H
