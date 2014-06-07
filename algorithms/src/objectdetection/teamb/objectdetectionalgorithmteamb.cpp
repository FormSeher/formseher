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

    const Line* lastDBLine = databaseObject.getLines()[currentLineNumber-1];
    const Line* currentDBLine = databaseObject.getLines()[currentLineNumber];

    //currentDbline = linTocheck; lastdbline = lastFoundline, -1 is the line before line to check
    // @reminder
    // myRating has to be <= maxRatingPerLine
    // as maxRatingPerLine is maximum(100)/lines of object

    // @howTo
    // consideredObject.setRating(consideredObject.getRating()+myRating);

    //calculate the vector between line.start and line.end for both objects and angle

    //points from lineToCheck
    cv::Point2i pointToCheckStart;
    cv::Point2i pointToCheckEnd;

    //points from lastFoundLine
    cv::Point2i lastPointToCheckStart;
    cv::Point2i lastPointToCheckEnd;

    //points from currentDBLine
    cv::Point2i dbStartPoint;
    cv::Point2i dbEndPoint;

    //points from lastDBLine
    cv::Point2i lastDBPointStart;
    cv::Point2i lastDBPointEnd;

    pointToCheckStart = lineToCheck.getStart();
    pointToCheckEnd = lineToCheck.getEnd();

    lastPointToCheckStart = lastFoundLine->getStart();
    lastPointToCheckEnd = lastFoundLine->getEnd();

    dbStartPoint = currentDBLine->getStart();
    dbEndPoint = currentDBLine->getEnd();

    lastDBPointStart = lastDBLine->getStart();
    lastDBPointEnd = lastDBLine->getEnd();


    //make vector between start and end point

    cv::Point2i vectorCurrentPoint;
    cv::Point2i vectorCurrentPointLast;

    cv::Point2i vectorDbPoint;
    cv::Point2i vectorDbPointLast;

    cv::Point2i vectorBetweenDBLines;
    cv::Point2i vectorBetweenObjectLines;
    //the vector of the the start and end point, for current and last line
    //b - a
    vectorCurrentPoint = pointToCheckEnd - pointToCheckStart;
    vectorCurrentPointLast = lastPointToCheckEnd - lastPointToCheckStart;

    vectorDbPoint = dbEndPoint - dbStartPoint;
    vectorDbPointLast = lastDBPointEnd - lastDBPointStart;

    //space beetwen the two lines
    vectorBetweenDBLines = dbStartPoint - lastDBPointEnd;
    vectorBetweenObjectLines = pointToCheckStart - lastPointToCheckEnd;

    //calculate angle between current and last line, skalarprodukt without cos
    //phi = (a1*b1) + (an * bn) / |a| * |b|
    double currentPointAngle;
    double dbPointAngle;

    int numeratorCurrentVector;
    double denominatorCurrentVector;

    int numeratorDbVector;
    double denominatorDbVector;

    //angle for current and next line
    numeratorCurrentVector = vectorCurrentPoint.x * vectorCurrentPointLast.x + vectorCurrentPoint.y * vectorCurrentPointLast.y;
    denominatorCurrentVector = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y)
                                * formseher::math::sqrtFast(vectorCurrentPointLast.x * vectorCurrentPointLast.x + vectorCurrentPointLast.y * vectorCurrentPointLast.y);

    currentPointAngle = numeratorCurrentVector / denominatorCurrentVector;

    //angle for current and next db line
    numeratorDbVector = vectorDbPoint.x * vectorDbPointLast.x + vectorDbPoint.y * vectorDbPointLast.y;
    denominatorDbVector = formseher::math::sqrtFast(vectorDbPoint.x * vectorDbPoint.x + vectorDbPoint.y * vectorDbPoint.y)
                            * formseher::math::sqrtFast(vectorDbPointLast.x * vectorDbPointLast.x + vectorDbPointLast.y * vectorDbPointLast.y);

    dbPointAngle = numeratorDbVector / denominatorDbVector;

    //now make with the vector dimension and angle rating values


    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0
    //|a|= sqrt(a1^2+an^2)

    //get the length
    double lengthCurrentLine = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y);
    double lengthCurrentLineLast = formseher::math::sqrtFast(vectorCurrentPointLast.x * vectorCurrentPointLast.x + vectorCurrentPointLast.y * vectorCurrentPointLast.y);

    double lengthDbCurrentLine = formseher::math::sqrtFast(vectorDbPoint.x * vectorDbPoint.x + vectorDbPoint.y * vectorDbPoint.y);
    double lengthDbLineLast = formseher::math::sqrtFast(vectorDbPointLast.x * vectorDbPointLast.x + vectorDbPointLast.y * vectorDbPointLast.y);

    double distanceBetweenDBLines = formseher::math::sqrtFast(vectorBetweenDBLines.x * vectorBetweenDBLines.x + vectorBetweenDBLines.y * vectorBetweenDBLines.y);
    double distanceBetweenObjectLines = formseher::math::sqrtFast(vectorBetweenObjectLines.x * vectorBetweenObjectLines.x + vectorBetweenObjectLines.y * vectorBetweenObjectLines.y);

    //now compare and set the rating, the current line to db current line

    double smallerThenDbThreshold = 1.2;// the dbline is 1.2 so big as the lineToCheck
    double biggerThenDbThreshold = 0.8;// the lineToCheck is 1.2 so big as the dbline
    double distanceThresholdMax = 1.2;
    double distanceThresholdMin = 0.85;

    //set rating
    //check for the point coordinates start and end if distance is to high ==>first

    double tenPointRating = maxRatingPerLine / 10;
    double lengthAndPosiRating = tenPointRating;


    if(distanceBetweenDBLines / distanceBetweenObjectLines < distanceThresholdMax || distanceBetweenDBLines / distanceBetweenObjectLines > distanceThresholdMin)//check the distance
    {
        lengthAndPosiRating = tenPointRating * 3;

        if(lengthDbCurrentLine / lengthCurrentLine < smallerThenDbThreshold || lengthDbCurrentLine / lengthCurrentLine > biggerThenDbThreshold)// check the length
        {
            lengthAndPosiRating = tenPointRating;
            lengthAndPosiRating = tenPointRating * 4;

            if(lengthDbLineLast / lengthCurrentLineLast < smallerThenDbThreshold || lengthDbLineLast / lengthCurrentLineLast > biggerThenDbThreshold)
            {
                lengthAndPosiRating = tenPointRating;
                lengthAndPosiRating = tenPointRating * 6;
            }
            else//point coord. ok, length ok but dbline length is wrong
            {
                lengthAndPosiRating = tenPointRating;
                lengthAndPosiRating = tenPointRating * 5;
            }
        }
        else//when point coord. is ok but length of lineToCheck is wrong
        {
            lengthAndPosiRating = tenPointRating;
            lengthAndPosiRating = tenPointRating * 1;
        }
    }
    else//rate when point coord. are very wrong
    {
        lengthAndPosiRating = tenPointRating;
    }

    // @toDo:
    // compare the angle of given lines with the angle of first and second line of object
    // do not calculate angles ! takes to much time !
    //      use comparisons instead
    // keep in mind that angles will never match
    //      -> small variances are ok

    //now compare the angle

    double angleThreshold1 = 0.1;//its allmost 10° +-2
    double angleThreshold2 = 0.2;//its allmost 20° +-2
    double angleThreshold3 = 0.3;//its allmost 30° +-2
    double angleRating;

    if(dbPointAngle - currentPointAngle <= angleThreshold1 || dbPointAngle - currentPointAngle >= -angleThreshold1)
    {
        angleRating = tenPointRating * 4;
    }
    else if(dbPointAngle - currentPointAngle <= angleThreshold2 || dbPointAngle - currentPointAngle >= -angleThreshold2)
    {
         angleRating = tenPointRating * 3;
    }
    else if(dbPointAngle - currentPointAngle <= angleThreshold3 || dbPointAngle - currentPointAngle >= -angleThreshold3)
    {
        angleRating = tenPointRating * 2;
    }
    else
    {
        angleRating = tenPointRating;
    }

    double completeRating = lengthAndPosiRating + angleRating;

    consideredObject.setRating(consideredObject.getRating()+completeRating);
}

void ObjectDetectionAlgorithmTeamB::getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects, std::string objectName){

//    Object bestRatedObject;
//    bestRatedObject.setRating(0);

//    int bestRatedObjectIndex = 0;

    for(uint currentObjectIndex = 0; currentObjectIndex < unfinishedObjects.size(); currentObjectIndex++){

        // skipped as many objects of same type can be in a picture
//        if(unfinishedObjects[currentObjectIndex].getRating() > bestRatedObject.getRating()){
//            bestRatedObject = unfinishedObjects[currentObjectIndex];
//        }

        // 70 == 70%
        if(unfinishedObjects[currentObjectIndex].getRating() > 70){
            foundObjects.push_back(unfinishedObjects[currentObjectIndex]);
        }
    }
//    bestRatedObject.setName(objectName);
//    foundObjects.push_back(bestRatedObject);
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

