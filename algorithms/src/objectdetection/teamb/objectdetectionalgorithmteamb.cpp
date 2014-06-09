#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"
#include <set>
#include "objectdetection/model.h"
#include "objectdetection/object.h"
#include "line.h"
#include "objectdetection/databaseutils.h"
#include "mathutil.h"
#include <iostream>

namespace formseher
{

ObjectDetectionAlgorithmTeamB::ObjectDetectionAlgorithmTeamB()
{

}

int ObjectDetectionAlgorithmTeamB::rateObject(Object consideredObject, Line lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine){

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

    cv::Point2i vectorBetweenDBLinesReverse;
    cv::Point2i vectorBetweenObjectLinesReverse;


    //the vector of the the start and end point, for current and last line
    //b - a
    vectorCurrentPoint = pointToCheckEnd - pointToCheckStart;
    vectorCurrentPointLast = lastPointToCheckEnd - lastPointToCheckStart;

    vectorDbPoint = dbEndPoint - dbStartPoint;
    vectorDbPointLast = lastDBPointEnd - lastDBPointStart;

    //space beetwen the two lines
    vectorBetweenDBLines = dbStartPoint - lastDBPointEnd;
    vectorBetweenObjectLines = pointToCheckStart - lastPointToCheckEnd;

    vectorBetweenDBLinesReverse = lastDBPointEnd - dbStartPoint;
    vectorBetweenObjectLinesReverse = lastPointToCheckEnd - pointToCheckStart;

    //calculate angle between current and last line, skalarprodukt without cos
    //phi = (a1*b1) + (an * bn) / |a| * |b|
    double currentPointAngle = getAngleOfLines(vectorCurrentPoint, vectorCurrentPointLast);
    double dbPointAngle = getAngleOfLines(vectorDbPoint, vectorDbPointLast);

    //now make with the vector dimension and angle rating values


    // @toDo:
    // compare the distance between start and end points
    // if distance if too high return with 0
    //|a|= sqrt(a1^2+an^2)

    //get the length
    double lengthCurrentLine = getLineLength(vectorCurrentPoint.x, vectorCurrentPoint.y);
    double lengthCurrentLineLast = getLineLength(vectorCurrentPointLast.x, vectorCurrentPointLast.y);
    double lengthDbCurrentLine = getLineLength(vectorDbPoint.x, vectorDbPoint.y);
    double lengthDbLineLast = getLineLength(vectorDbPointLast.x, vectorDbPointLast.y);
    double distanceBetweenDBLines = getLineLength(vectorBetweenDBLines.x, vectorBetweenDBLines.y);
    double distanceBetweenObjectLines = getLineLength(vectorBetweenObjectLines.x, vectorBetweenObjectLines.y);

    double distanceBetweenDBLinesReverse = getLineLength(vectorBetweenDBLinesReverse.x, vectorBetweenDBLinesReverse.y);
    double distanceBetweenObjectLinesReverse = getLineLength(vectorBetweenObjectLinesReverse.x, vectorBetweenObjectLinesReverse.y);

    //now compare and set the rating, the current line to db current line

    double smallerThenDbThreshold = 1.2;// the dbline is 1.2 so big as the lineToCheck
    double biggerThenDbThreshold = 0.8;// the lineToCheck is 1.2 so big as the dbline
    double distanceThresholdMax = 1.2;
    double distanceThresholdMin = 0.85;

    //set rating
    //check for the point coordinates start and end if distance is to high ==>first

    double tenPointRating = maxRatingPerLine / 10;
    double lengthAndPosiRating = tenPointRating;


    if(distanceBetweenDBLines / distanceBetweenObjectLines < distanceThresholdMax && distanceBetweenDBLines / distanceBetweenObjectLines > distanceThresholdMin ||
            distanceBetweenDBLinesReverse / distanceBetweenObjectLinesReverse < distanceThresholdMax && distanceBetweenDBLinesReverse / distanceBetweenObjectLinesReverse > distanceThresholdMin)//check the distance
    {
        lengthAndPosiRating = tenPointRating * 4.5;

        if(lengthDbCurrentLine / lengthCurrentLine < smallerThenDbThreshold && lengthDbCurrentLine / lengthCurrentLine > biggerThenDbThreshold)// check the length
        {
            lengthAndPosiRating = tenPointRating * 4.75;

            if(lengthDbLineLast / lengthCurrentLineLast < smallerThenDbThreshold && lengthDbLineLast / lengthCurrentLineLast > biggerThenDbThreshold)
            {
                lengthAndPosiRating = tenPointRating * 5;
            }
        }
    }
    else//rate when point coord. are very wrong
    {
        lengthAndPosiRating = 0;
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

    if(dbPointAngle - currentPointAngle <= angleThreshold3 && dbPointAngle - currentPointAngle >= -angleThreshold3)
    {
        angleRating = tenPointRating * 3;

       if(dbPointAngle - currentPointAngle <= angleThreshold2 && dbPointAngle - currentPointAngle >= -angleThreshold2)
        {
             angleRating = tenPointRating * 4;

             if(dbPointAngle - currentPointAngle <= angleThreshold1 && dbPointAngle - currentPointAngle >= -angleThreshold1)
             {
                 angleRating = tenPointRating * 5;
             }
        }
    }
    else
    {
        angleRating = 0;
    }
    return lengthAndPosiRating + angleRating;
}

double ObjectDetectionAlgorithmTeamB::getLineLength(int x, int y)
{
    return formseher::math::sqrtFast(x * x + y * y);
}

double ObjectDetectionAlgorithmTeamB::getAngleOfLines(cv::Point2i vectorCurrentPoint, cv::Point2i vectorCurrentPointLast)
{
    int numeratorCurrentVector;
    double denominatorCurrentVector;

    numeratorCurrentVector = vectorCurrentPoint.x * vectorCurrentPointLast.x + vectorCurrentPoint.y * vectorCurrentPointLast.y;

    denominatorCurrentVector = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y)
                                * formseher::math::sqrtFast(vectorCurrentPointLast.x * vectorCurrentPointLast.x + vectorCurrentPointLast.y * vectorCurrentPointLast.y);

    return numeratorCurrentVector / denominatorCurrentVector;
}

void ObjectDetectionAlgorithmTeamB::getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects, std::string objectName){

    for(uint currentObjectIndex = 0; currentObjectIndex < unfinishedObjects.size(); currentObjectIndex++){

        // 70 == 70%
        if(unfinishedObjects[currentObjectIndex].getRating() > 70){
            unfinishedObjects[currentObjectIndex].setName(objectName);
            foundObjects.push_back(unfinishedObjects[currentObjectIndex]);
        }
    }
}

std::vector<Object> ObjectDetectionAlgorithmTeamB::calculate(std::vector<Line> lines){

    std::vector<Object> foundObjects;
    std::vector<Object> unfinishedObjects;

    // iterate through database objects
    for(auto model : databaseModels){

        // maximum rating for 1 line
        float maxRatingPerLine = 100 / model.getLines().size();

        // create possible object for every line
        for(uint firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

            Object obj;
            obj.addLine(lines[firstLineIndex]);
            obj.setRating(maxRatingPerLine);
            unfinishedObjects.push_back(obj);
        }

        // iterate through lines of an object starting at 2nd line (as first lines are already in) to check all other lines
        for(uint objectLineIndex = 1; objectLineIndex < model.getLines().size(); objectLineIndex++){

            std::vector<Object> newUnfinishedObjects;

            // check other object lines with found lines
            for(uint foundObjectsIndex = 0; foundObjectsIndex < unfinishedObjects.size(); foundObjectsIndex++){

                // get possible next line
                for(uint nextLineIndex = 0; nextLineIndex < lines.size(); nextLineIndex++){

                    int receivedRating = rateObject(unfinishedObjects[foundObjectsIndex], lines[nextLineIndex], model, objectLineIndex, maxRatingPerLine);

                    // if rating is not high enough continue
                    // rating has to be atleast 60% of maximum
                    if(unfinishedObjects[foundObjectsIndex].getRating() + receivedRating > (maxRatingPerLine * (objectLineIndex + 1)) * 0.6){

                        // if rating was ok add line to object
                        Object newObj = unfinishedObjects[foundObjectsIndex];
                        newObj.addLine(lines[nextLineIndex]);
                        newObj.setRating(newObj.getRating() + receivedRating);

                        newUnfinishedObjects.push_back(newObj);
                    }
                    else{
                        continue;
                    }
                }
            }
            unfinishedObjects = newUnfinishedObjects;
        }
        getBestRatedObject(unfinishedObjects, foundObjects, model.getName());
    }
    return foundObjects;
}

} // namespace formseher

