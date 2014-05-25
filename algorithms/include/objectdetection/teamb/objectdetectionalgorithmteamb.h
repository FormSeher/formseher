#ifndef OBJECTDETECTIONALGORITHMTEAMB_H
#define OBJECTDETECTIONALGORITHMTEAMB_H

#include "objectdetection/objectdetectionalgorithm.h"
#include "line.h"

namespace formseher
{

class ObjectDetectionAlgorithmTeamB : public ObjectDetectionAlgorithm
{

public:
    ObjectDetectionAlgorithmTeamB();

    virtual std::vector<Object*> calculate(std::vector<Line> lines) = 0;

private:
    int databaseSize;
    std::vector<Object> databaseObjects;

    void getAllDatabaseObjects();
    void getFirstRating(int& rating, Line firstLine, Line secondLine, Object databaseObject);
    void getRating(int& rating, Object consideredObject, Line lineToCheck, Object databaseObject, int currentLineNumber);
    void getBestRatedObjects(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects);

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHMTEAMB_H
