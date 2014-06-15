#ifndef OBJECTDETECTIONALGORITHMTEAMB_H
#define OBJECTDETECTIONALGORITHMTEAMB_H

#include "objectdetection/objectdetectionalgorithm.h"
#include "line.h"
#include "objectdetection/model.h"
#include "objectdetection/object.h"

typedef unsigned int uint;

namespace formseher
{

    class ObjectDetectionAlgorithmTeamB : public ObjectDetectionAlgorithm
    {

    public:

        ObjectDetectionAlgorithmTeamB(int minRating, double maxAngleThreshold, double maxDistanceThreshold);

        std::vector<Object> calculate(std::vector<Line> lines);

    private:

        double rateObject(Object& consideredObject, Line& lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine);
        void getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>& foundObjects, std::string objectName);
        double getLineLength(int x, int y);
        double getAngleOfLines(cv::Point2i vectorCurrentPoint, cv::Point2i vectorCurrentPointLast);

        int minRating = 80;
        double maxAngleThreshold = 0.15;
        double maxDistanceThreshold = 0.2;
    };

} //  namespace formseher
#endif // OBJECTDETECTIONALGORITHMTEAMB_H
