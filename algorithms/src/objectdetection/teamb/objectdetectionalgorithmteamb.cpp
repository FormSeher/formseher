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

double ObjectDetectionAlgorithmTeamB::rateObject(Object consideredObject, Line lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine){

    const Line* lastFoundLine = consideredObject.getLines()[currentLineNumber-1];

    const Line* lastDBLine = databaseObject.getLines()[currentLineNumber-1];
    const Line* currentDBLine = databaseObject.getLines()[currentLineNumber];

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

    cv::Point2i vectorBetweenObjectLinesReverse;
    cv::Point2i vectorBetweenObjectLinesReverse2;
    cv::Point2i vectorBetweenObjectLinesReverse3;


    //the vector of the the start and end point, for current and last line
    //b - a
    vectorCurrentPoint = pointToCheckEnd - pointToCheckStart;
    vectorCurrentPointLast = lastPointToCheckEnd - lastPointToCheckStart;

    vectorDbPoint = dbEndPoint - dbStartPoint;
    vectorDbPointLast = lastDBPointEnd - lastDBPointStart;

    //space beetwen the two lines
    vectorBetweenDBLines = dbStartPoint - lastDBPointEnd;

    vectorBetweenObjectLines = pointToCheckStart - lastPointToCheckEnd;
    vectorBetweenObjectLinesReverse = pointToCheckEnd - lastPointToCheckEnd;
    vectorBetweenObjectLinesReverse2 = pointToCheckStart - lastPointToCheckStart;
    vectorBetweenObjectLinesReverse3 = pointToCheckEnd - lastPointToCheckStart;

    //calculate angle between current and last line, skalarprodukt without cos
    //phi = (a1*b1) + (an * bn) / |a| * |b|
    double currentPointAngle = getAngleOfLines(vectorCurrentPoint, vectorCurrentPointLast);
    double dbPointAngle = getAngleOfLines(vectorDbPoint, vectorDbPointLast);

    //get the length
    double lengthCurrentLine = getLineLength(vectorCurrentPoint.x, vectorCurrentPoint.y);
    double lengthCurrentLineLast = getLineLength(vectorCurrentPointLast.x, vectorCurrentPointLast.y);
    double lengthDbCurrentLine = getLineLength(vectorDbPoint.x, vectorDbPoint.y);
    double lengthDbLineLast = getLineLength(vectorDbPointLast.x, vectorDbPointLast.y);
    double distanceBetweenDBLines = getLineLength(vectorBetweenDBLines.x, vectorBetweenDBLines.y);
    double distanceBetweenObjectLines = getLineLength(vectorBetweenObjectLines.x, vectorBetweenObjectLines.y);
    double distanceBetweenObjectLinesReverse = getLineLength(vectorBetweenObjectLinesReverse.x, vectorBetweenObjectLinesReverse.y);
    double distanceBetweenObjectLinesReverse2 = getLineLength(vectorBetweenObjectLinesReverse2.x, vectorBetweenObjectLinesReverse2.y);
    double distanceBetweenObjectLinesReverse3 = getLineLength(vectorBetweenObjectLinesReverse3.x, vectorBetweenObjectLinesReverse3.y);

    //now compare and set the rating, the current line to db current line

    double smallerThenDbThreshold = 1.2;// the dbline is 1.2 so big as the lineToCheck
    double biggerThenDbThreshold = 0.8;// the lineToCheck is 1.2 so big as the dbline;
    double distanceThreshold1 = 0.5;
    double distanceThreshold2 = 0.3;
    double distanceThreshold3 = 0.1;


    double tenPointRating = maxRatingPerLine / 10;
    double lengthAndPosiRating = 0;// tenPointRating;

    // get a relative value of distance that says how much space is between end of last line and start of new line compared to the length of new line
    double relDistanceBetweenDBPoints = distanceBetweenDBLines/lengthDbCurrentLine;
    double relDistanceBetweenLinePoints = distanceBetweenObjectLines/lengthCurrentLine;
    double relDistanceBetweenLinePointsRevert = distanceBetweenObjectLinesReverse/lengthCurrentLine;
    double relDistanceBetweenLinePointsRevert2 = distanceBetweenObjectLinesReverse2/lengthCurrentLine;
    double relDistanceBetweenLinePointsRevert3 = distanceBetweenObjectLinesReverse3/lengthCurrentLine;

    double relValNorm = relDistanceBetweenDBPoints - relDistanceBetweenLinePoints;
    double relValRev = relDistanceBetweenDBPoints - relDistanceBetweenLinePointsRevert;
    double relValRev2 = relDistanceBetweenDBPoints - relDistanceBetweenLinePointsRevert2;
    double relValRev3 = relDistanceBetweenDBPoints - relDistanceBetweenLinePointsRevert3;

    //check the distance
    if((relValNorm < distanceThreshold1 && relValNorm > -distanceThreshold1) || (relValRev < distanceThreshold1 && relValRev > -distanceThreshold1)
            ||(relValRev2 < distanceThreshold1 && relValRev2 > -distanceThreshold1) || (relValRev3 < distanceThreshold1 && relValRev3 > -distanceThreshold1))
    {
        lengthAndPosiRating = tenPointRating * 2.0;

        if((relValNorm < distanceThreshold2 && relValNorm > -distanceThreshold2) || (relValRev < distanceThreshold2 && relValRev > -distanceThreshold2)
            ||(relValRev2 < distanceThreshold2 && relValRev2 > -distanceThreshold2) || (relValRev3 < distanceThreshold2 && relValRev3 > -distanceThreshold2))
        {
            lengthAndPosiRating = tenPointRating * 3.0;

            if((relValNorm < distanceThreshold3 && relValNorm > -distanceThreshold3) || (relValRev < distanceThreshold3 && relValRev > -distanceThreshold3)
               ||(relValRev2 < distanceThreshold3 && relValRev2 > -distanceThreshold3) || (relValRev3 < distanceThreshold3 && relValRev3 > -distanceThreshold3))
            {
                lengthAndPosiRating = tenPointRating * 4.0;
            }
        }

        if(lengthDbCurrentLine / lengthCurrentLine < smallerThenDbThreshold && lengthDbCurrentLine / lengthCurrentLine > biggerThenDbThreshold)// check the length
        {
            lengthAndPosiRating += tenPointRating * 0.75;

            if(lengthDbLineLast / lengthCurrentLineLast < smallerThenDbThreshold && lengthDbLineLast / lengthCurrentLineLast > biggerThenDbThreshold)
            {
                lengthAndPosiRating += tenPointRating * 0.25;
            }
        }

    }
    else//rate when point coord. are very wrong
    {
        lengthAndPosiRating = 0;
    }

    //now compare the angle
    double angleThreshold1 = 0.1;//its allmost 10° +-2
    double angleThreshold2 = 0.2;//its allmost 20° +-2
    double angleThreshold3 = 0.3;//its allmost 30° +-2
    double angleRating;

    // as angle can be positive and negative consider both
    double relPosAngleVal = dbPointAngle - currentPointAngle;
    double relNegAngleVal = dbPointAngle + currentPointAngle;

    if((relPosAngleVal <= angleThreshold3 && relPosAngleVal >= -angleThreshold3) || (relNegAngleVal <= angleThreshold3 && relNegAngleVal >= -angleThreshold3))
    {
        angleRating = tenPointRating * 3;

       if((relPosAngleVal <= angleThreshold2 && relPosAngleVal >= -angleThreshold2) || (relNegAngleVal <= angleThreshold2 && relNegAngleVal >= -angleThreshold2))
        {
             angleRating = tenPointRating * 4;

             if((relPosAngleVal <= angleThreshold1 && relPosAngleVal >= -angleThreshold1) || (relNegAngleVal <= angleThreshold1 && relNegAngleVal >= -angleThreshold1))
             {
                 angleRating = tenPointRating * 5;
             }
        }
    }
    else
    {
        angleRating = 0;
    }
    if(lengthAndPosiRating > 0 && angleRating > 0){
        return lengthAndPosiRating + angleRating;
    }
    else return 0;
}

double ObjectDetectionAlgorithmTeamB::getLineLength(int x, int y)
{
    return formseher::math::sqrtFast(x * x + y * y);
}

double ObjectDetectionAlgorithmTeamB::getAngleOfLines(cv::Point2i vectorCurrentPoint, cv::Point2i vectorCurrentPointLast)
{
    double numeratorCurrentVector;
    double denominatorCurrentVector;

    numeratorCurrentVector = vectorCurrentPoint.x * vectorCurrentPointLast.x + vectorCurrentPoint.y * vectorCurrentPointLast.y;

    denominatorCurrentVector = formseher::math::sqrtFast(vectorCurrentPoint.x * vectorCurrentPoint.x + vectorCurrentPoint.y * vectorCurrentPoint.y)
                                * formseher::math::sqrtFast(vectorCurrentPointLast.x * vectorCurrentPointLast.x + vectorCurrentPointLast.y * vectorCurrentPointLast.y);

    return numeratorCurrentVector / denominatorCurrentVector;
}

void ObjectDetectionAlgorithmTeamB::getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects, std::string objectName){

    for(uint currentObjectIndex = 0; currentObjectIndex < unfinishedObjects.size(); currentObjectIndex++){
        // 80 == 80%
        if(unfinishedObjects[currentObjectIndex].getRating() > 85){
            unfinishedObjects[currentObjectIndex].setName(objectName);
            foundObjects.push_back(unfinishedObjects[currentObjectIndex]);

        }
    }
}

std::vector<Object> ObjectDetectionAlgorithmTeamB::calculate(std::vector<Line> lines){

    std::vector<Object> foundObjects;

    // iterate through database objects
    for(auto model : databaseModels){

        std::vector<Object> unfinishedObjects;

        // maximum rating for 1 line
        float maxRatingPerLine = 100 / model.getLines().size();

        // create possible object for every line
        for(uint firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

            Object obj;
            obj.addLine(lines[firstLineIndex]);
            obj.setRating(maxRatingPerLine - maxRatingPerLine * 0.2);
            unfinishedObjects.push_back(obj);
        }

        std::vector<Object> newUnfinishedObjects;
        // iterate through lines of an object starting at 2nd line (as first lines are already in) to check all other lines
        for(uint objectLineIndex = 1; objectLineIndex < model.getLines().size(); objectLineIndex++){

            newUnfinishedObjects.clear();

            // check other object lines with found lines
            for(uint foundObjectsIndex = 0; foundObjectsIndex < unfinishedObjects.size(); foundObjectsIndex++){

                // get possible next line
                for(uint nextLineIndex = 0; nextLineIndex < lines.size(); nextLineIndex++){

                    double receivedRating = rateObject(unfinishedObjects[foundObjectsIndex], lines[nextLineIndex], model, objectLineIndex, maxRatingPerLine);

                    // if rating is not high enough continue
                    // rating has to be atleast 60% of maximum
//                    if(unfinishedObjects[foundObjectsIndex].getRating() + receivedRating >= (maxRatingPerLine * (objectLineIndex + 1)) * 0.1){
                    if(receivedRating > 0){

                        // if rating was ok add line to object
                        Object newObj(unfinishedObjects[foundObjectsIndex]);
                        newObj.addLine(lines[nextLineIndex]);
                        newObj.setRating(newObj.getRating() + receivedRating);

                        newUnfinishedObjects.push_back(newObj);
                    }
                    else{
                        continue;
                    }
                }
            }
            unfinishedObjects.clear();
            for(auto newObj : newUnfinishedObjects){
                unfinishedObjects.push_back(newObj);
            }
        }
        getBestRatedObject(unfinishedObjects, foundObjects, model.getName());
    }
    return foundObjects;
}

} // namespace formseher

