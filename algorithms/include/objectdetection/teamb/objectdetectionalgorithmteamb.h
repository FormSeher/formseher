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

        /**
         * @brief constructor of object detection algorithm of teamB
         * @param minRating - minimum rating for objects to be considered as found and to be returned
         * @param maxAngleThreshold - maximum threshold of angle between two lines from picture compared to model
         * @param maxDistanceThreshold - maximum threshold of distance between start and end points of two lines from picture compared to model
         * @param midPointEnvironment - maximum space of object midpoints. the smaller it is the more likely bounding boxes of objects will oberlap
         * @param fastMode - enable / disable fast mode
         */
        ObjectDetectionAlgorithmTeamB(int minRating, double maxAngleThreshold, double maxDistanceThreshold, int midPointEnvironment, bool fastMode);

        /*! @copydoc ObjectDetection::calculate()
         */
        std::vector<Object> calculate(std::vector<Line> lines);

    private:

        /**
         * @brief compare two lines from picture with two lines of model. Rate their angles, distance between start and end points and line lengths
         * @param consideredObject : object to check
         * @param lineToCheck : new line from picture to check if suits into considered object
         * @param databaseObject : model from database
         * @param currentLineNumber : actual number to check from model
         * @param maxRatingPerLine : maximum rating the linepair can receive
         * @return the rating of line pair
         */
        double rateObject(Object& consideredObject, Line& lineToCheck, Model databaseObject, int currentLineNumber, float maxRatingPerLine);

        /**
         * @brief check all possible to be returned objects by rating. Also remove objects whos bouning boxes would overlap
         * @param unfinishedObjects : objects to be checked by rating
         * @param foundObjects : vector of objects to be returned
         * @param objectName : name of model to be added to objects
         */
        void getBestRatedObject(std::vector<Object> unfinishedObjects, std::vector<Object>* foundObjects, std::string objectName);

        /**
         * @brief get length of vector
         * @param x
         * @param y
         * @return length
         */
        double getLineLength(int x, int y);

        /**
         * @brief calculate the angle between two lines
         * @param vectorCurrentPoint : current line ( line 1 )
         * @param vectorCurrentPointLast : last line of object ( line 2 )
         * @return the calculated angle
         */
        double getAngleOfLines(cv::Point2i vectorCurrentPoint, cv::Point2i vectorCurrentPointLast);

        int minRating = 60;
        double maxAngleThreshold = 0.2;
        double maxDistanceThreshold = 0.2;
        int midPointEnvironment = 10;
        bool fastMode = true;
    };

} //  namespace formseher
#endif // OBJECTDETECTIONALGORITHMTEAMB_H
