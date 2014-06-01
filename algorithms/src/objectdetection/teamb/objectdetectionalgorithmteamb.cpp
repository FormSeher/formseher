#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"
#include <set>
#include "objectdetection/model.h"
#include "objectdetection/object.h"
#include "line.h"
#include "objectdetection/databaseutils.h"
#include "mathutil.h"

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
    const Line* nextConsideredObjectLine = consideredObject.getLines()[currentLineNumber + 1];

//    const Line* currentDBLine = databaseObject.getLines()[currentLineNumber];
    const Line* nextDBLine = databaseObject.getLines()[currentLineNumber + 1];

    //calculate the vector between line.start and line.end for both objects and angle
    cv::Point2i pointToCheckStart;
    cv::Point2i pointToCheckEnd;

    cv::Point2i nextPointToCheckStart;
    cv::Point2i nextPointToCheckEnd;

    cv::Point2i dbStartPoint;
    cv::Point2i dbEndPoint;

    cv::Point2i dbNextPointStart;
    cv::Point2i dbNextPointEnd;

    pointToCheckStart = lineToCheck.getStart();
    pointToCheckEnd = lineToCheck.getEnd();

    nextPointToCheckStart = nextConsideredObjectLine->getStart();
    nextPointToCheckEnd = nextConsideredObjectLine->getEnd();

    dbStartPoint = currentDBLine->getStart();
    dbEndPoint = currentDBLine->getEnd();

    dbNextPointStart = nextDBLine->getStart();
    dbNextPointEnd = nextDBLine->getEnd();


    //make vector between start and end point

    cv::Point2i vectorCurrentPoint;
    cv::Point2i vectorCurrentPointNext;

    cv::Point2i vectorDbPoint;
    cv::Point2i vectorDbPointNext;

    //the vector of the the start and end point, for current and next line
    //b - a
    vectorCurrentPoint = pointToCheckEnd - pointToCheckStart;
    vectorCurrentPointNext = nextPointToCheckEnd - nextPointToCheckStart;

    vectorDbPoint = dbEndPoint - dbStartPoint;
    vectorDbPointNext = dbNextPointEnd - dbNextPointStart;

    //calculate angle between current and next line, skalarprodukt without cos
    //phi = (a1*b1) + (an * bn) / |a| * |b|
    double currentPointAngle;
    double dbPointAngle;

    int numeratorCurrentPoint;
    double denominatorCurrentPoint;

    int numeratorDbPoint;
    double denominatorDbPoint;

    //angle for current and next line
    numeratorCurrentPoint = vectorCurrentPoint.x * vectorCurrentPointNext.x + vectorCurrentPoint.y * vectorCurrentPointNext.y;
    denominatorCurrentPoint = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y)
                                * formseher::math::sqrtFast(vectorCurrentPointNext.x * vectorCurrentPointNext.x + vectorCurrentPointNext.y * vectorCurrentPointNext.y);

    currentPointAngle = numeratorCurrentPoint / denominatorCurrentPoint;

    //angle for current and next db line
    numeratorDbPoint = vectorDbPoint.x * vectorDbPointNext.x + vectorDbPoint.y * vectorDbPointNext.y;
    denominatorDbPoint = formseher::math::sqrtFast(vectorDbPoint.x * vectorDbPoint.x + vectorDbPoint.y * vectorDbPoint.y)
                            * formseher::math::sqrtFast(vectorDbPointNext.x * vectorDbPointNext.x + vectorDbPointNext.y * vectorDbPointNext.y);

    dbPointAngle = numeratorDbPoint / denominatorDbPoint;

    //now make with the vector dimension and angle rating values


    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0
    //|a|= sqrt(a1^2+an^2)

    //get the length
    double lengthCurrentLine = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y);
    double lengthCurrentLineNext = formseher::math::sqrtFast(vectorCurrentPointNext.x * vectorCurrentPointNext.x + vectorCurrentPointNext.y * vectorCurrentPointNext.y);

    double lengthDbCurrentLine = formseher::math::sqrtFast(vectorDbPoint.x * vectorDbPoint.x + vectorDbPoint.y * vectorDbPoint.y);
    double lengthDbLineNext = formseher::math::sqrtFast(vectorDbPointNext.x * vectorDbPointNext.x + vectorDbPointNext.y * vectorDbPointNext.y);

    //now compare and set the rating, the current line to db current line, because next should be the same

    double smallerThenDbThreshold = 1.2;// the dbline is 1.2 so big as the lineToCheck
    double biggerThenDbThreshold = 0.8;// the lineToCheck is 1.2 so big as the dbline

    if(lengthDbCurrentLine / lengthCurrentLine > smallerThenDbThreshold || lengthDbCurrentLine / lengthCurrentLine < biggerThenDbThreshold)
    {

        // @reminder
        // myRating has to be <= maxRatingPerLine
        // as maxRatingPerLine is maximum(100)/lines of object
        //set rating

    }

    // @toDo:
    // compare the angle of given lines with the angle of first and second line of object
    // do not calculate angles ! takes to much time !
    //      use comparisons instead
    // keep in mind that angles will never match
    //      -> small variances are ok

    //now compare the angle

    double angleThreshold = 0.1;//its allmost 10° +-2

    if(dbPointAngle - currentPointAngle > angleThreshold || dbPointAngle - currentPointAngle < -angleThreshold);
    {
        // @reminder
        // myRating has to be <= maxRatingPerLine
        // as maxRatingPerLine is maximum(100)/lines of object
//        *rating = 0;
    }
}

void ObjectDetectionAlgorithmTeamB::getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects, std::string objectName){

    Object bestRatedObject;
    bestRatedObject.setRating(0);

    for(uint currentObjectIndex = 0; currentObjectIndex < unfinishedObjects.size(); currentObjectIndex++){
        if(unfinishedObjects[currentObjectIndex].getRating() > bestRatedObject.getRating()){
            bestRatedObject = unfinishedObjects[currentObjectIndex];
        }
    }
    bestRatedObject.setName(objectName);
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
        for(uint firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

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

    getBestRatedObject(unfinishedObjects, foundObjects, databaseObjects[currentObjectIndex].getName());
    }
    return foundObjects;
}

} // namespace formseher

