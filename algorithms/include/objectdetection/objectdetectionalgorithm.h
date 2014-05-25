#ifndef OBJECTDETECTIONALGORITHM_H
#define OBJECTDETECTIONALGORITHM_H

#include "object.h"
#include "line.h"

namespace formseher {

class ObjectDetectionAlgorithm
{
public:
    ObjectDetectionAlgorithm();

    virtual std::vector<Object*> calculate(std::vector<Line> lines) = 0;

private:
    int databaseSize;
    std::vector<Object> databaseObjects;

    void getAllDatabaseObjects();
    void getFirstRating(int& rating, Line firstLine, Line secondLine, Object databaseObject);
    void getRating(int& rating, Object consideredObject, Line lineToCheck, Object databaseObject, int currentLineNumber);
    void getBestRatedObjects(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects);

};

}   //  namespace formseher

#endif // OBJECTDETECTIONALGORITHM_H
