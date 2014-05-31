#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"
#include <set>
#include "objectdetection/model.h"
#include "objectdetection/object.h"
#include "line.h"
#include "objectdetection/databaseutils.h"

namespace formseher
{

ObjectDetectionAlgorithmTeamB::ObjectDetectionAlgorithmTeamB()
{
    getAllDatabaseObjects();
}

void ObjectDetectionAlgorithmTeamB::getAllDatabaseObjects(){

    DatabaseUtils dbu("pathToDB");
    databaseObjects = dbu.read();

    databaseSize = databaseObjects.size();
}

void ObjectDetectionAlgorithmTeamB::rateObject(Object& consideredObject, Line lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine){

    const Line* lastFoundLine = consideredObject.getLines()[currentLineNumber-1];
    // currentFoundLine == lineToCheck

    const Line* lastDBLine = databaseObject.getLines()[currentLineNumber-1];
    const Line* currentDBLine = databaseObject.getLines()[currentLineNumber];

    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0

    // @toDo:
    // compare the angle of given lines with the angle of first and second line of object
    // do not calculate angles ! takes to much time !
    //      use comparisons instead
    // keep in mind that angles will never match
    //      -> small variances are ok

    // @reminder
    // myRating has to be <= maxRatingPerLine
    // as maxRatingPerLine is maximum(100)/lines of object

    // @howTo
    // consideredObject.setRating(consideredObject.getRating()+myRating);

}

void ObjectDetectionAlgorithmTeamB::getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects){

    Object bestRatedObject;
    bestRatedObject.setRating(0);

    for(int currentObjectIndex = 0; currentObjectIndex < unfinishedObjects.size(); currentObjectIndex++){
        if(unfinishedObjects[currentObjectIndex].getRating() > bestRatedObject.getRating()){
            bestRatedObject = unfinishedObjects[currentObjectIndex];
        }
    }
    foundObjects.push_back(bestRatedObject);
}

std::vector<Object> ObjectDetectionAlgorithmTeamB::calculate(std::vector<Line> lines){

    std::vector<Object> foundObjects;
    std::vector<Object> unfinishedObjects;

    // iterate through database objects
    for(int currentObjectIndex = 0; currentObjectIndex < databaseSize; currentObjectIndex++){

        // maximum rating for 1 line
        float maxRatingPerLine = 100 / databaseObjects[currentObjectIndex].getLines().size();

        // create possible object for every line
        for(int firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

            Object obj;
            obj.addLine(lines[firstLineIndex]);
            obj.setRating(maxRatingPerLine);
            unfinishedObjects.push_back(obj);
        }

        // iterate through lines of an object starting at 2nd line (as first lines are already in) to check all other lines
        for(uint objectLineIndex = 1; objectLineIndex < databaseObjects[currentObjectIndex].getLines().size(); objectLineIndex++){

            std::vector<Object> newUnfinishedObjects;

            // check other object lines with found lines
            for(uint foundObjectsIndex = 0; foundObjectsIndex < unfinishedObjects.size(); foundObjectsIndex++){

                // get possible next line
                for(uint nextLineIndex = 0; nextLineIndex < lines.size(); nextLineIndex++){

                    rateObject(unfinishedObjects[foundObjectsIndex], lines[nextLineIndex], databaseObjects[currentObjectIndex], objectLineIndex, maxRatingPerLine);

                    // if rating is not high enough continue
                    // rating has to be atleast 60% of maximum
                    if(unfinishedObjects[foundObjectsIndex].getRating() > (maxRatingPerLine * (objectLineIndex + 1)) * 0.6){

                        // if rating was ok add line to object
                        Object newObj = unfinishedObjects[foundObjectsIndex];
                        newObj.addLine(lines[nextLineIndex]);

                        newUnfinishedObjects.push_back(newObj);
                    }
                    else{
                        continue;
                    }
                }
            }
            unfinishedObjects = newUnfinishedObjects;
        }

    getBestRatedObject(unfinishedObjects, foundObjects);
    }
    return foundObjects;
}

} // namespace formseher

