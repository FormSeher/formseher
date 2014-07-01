#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

Hypothesis::Hypothesis(const Model *model, double angleWeight, double coverWeight, double positionWeight)
    : model(model),
      angleWeight(angleWeight),
      coverWeight(coverWeight),
      positionWeight(positionWeight)
{
}

void Hypothesis::calculateRating()
{
    // Calculate scale for Ratings
    calculateScale();

    // Calculate angle rating
    calculateAngleRating();

    // Calculate cover rating
    calculateCoverageRating();

    calculatePositionRating();
}

Hypothesis::Hypothesis(const Hypothesis& hypothesis)
    : model(hypothesis.model),
      angleWeight(hypothesis.angleWeight),
      coverWeight(hypothesis.coverWeight),
      positionWeight(hypothesis.positionWeight),
      lineMatchMap(hypothesis.lineMatchMap),
      notMatchingLines(hypothesis.notMatchingLines)
{
}

double Hypothesis::getRating() const
{
    return ( angleRating * angleWeight + coverRating * coverWeight + positionRating * positionWeight) * 100.0;
}

bool Hypothesis::containsLine(const Line* line) const
{
    return ( lineMatchMap.find( (Line*) line ) != lineMatchMap.end() );
}

void Hypothesis::addLineMatch(const Line* pictureLine, const Line* databaseLine)
{
    if (pictureLine == nullptr)
    {
        notMatchingLines.push_back(databaseLine);
    }
    else
    {
        lineMatchMap.insert( std::pair<Line*, Line*>((Line*)pictureLine, (Line*)databaseLine) );
    }
}

bool Hypothesis::operator<(const Hypothesis& hypo) const
{
    return ( getRating() < hypo.getRating() );
}

void Hypothesis::calculateAngleRating()
{
    if(lineMatchMap.size() < 2)
    {
        angleRating = 1.0;
        return;
    }

    double totalError = 0.0;
    // prevIter is last element of lines to get a cyclic match:
    // line1 -> line2 -> line3 -> line1
    auto prevIter = --(lineMatchMap.end());
    auto currIter = lineMatchMap.begin();

    double angleObject;
    double angleModel;

    while(currIter != lineMatchMap.end())
    {
        // HINT: absolute values of dot products are used to treat
        // line (A -> B) as line (B -> A)

        // angleObject = last object line vector * current object line vector
        angleObject = std::fabs(prevIter->first->getDirectionVector().dot(currIter->first->getDirectionVector()));

        // angleModel = last model line vector * current model line vector
        angleModel = std::fabs(prevIter->second->getDirectionVector().dot(currIter->second->getDirectionVector()));

        // Add relative error
        totalError += std::fabs(angleModel - angleObject);

        // Increment iterators
        prevIter = currIter++;
    }

    // match = 100% - error
    angleRating = 1.0d - (totalError / (double)lineMatchMap.size());
}

void Hypothesis::calculateCoverageRating()
{
    double coverageError = 0.0;
    double scaledModelLength = 0.0;

    for(auto lineMatch : lineMatchMap)
    {
        scaledModelLength = lineMatch.second->getLength() * scaleFactor;

        // Prevent division by zero
        if(scaledModelLength != 0)
            coverageError += fabs( (lineMatch.first->getLength() - scaledModelLength) ) / scaledModelLength;
    }

    coverageError = coverageError / (double)lineMatchMap.size();

    this->coverRating = 1.0 - coverageError;

    if(this->coverRating < 0)
        this->coverRating = 0;
}

void Hypothesis::calculatePositionRating()
{
    std::pair<cv::Point2d, cv::Point2d> centers = calculateCenters();

    double objectDistance = 0;
    double modelDistance = 0;
    double distanceError = 0;
    cv::Point2d centerPoint;

    for(auto lineMatch : lineMatchMap)
    {
        centerPoint = lineMatch.first->getCenterPoint();
        objectDistance = cv::norm(centerPoint - centers.first);

        centerPoint = lineMatch.second->getCenterPoint();
        modelDistance = cv::norm(centerPoint - centers.second) * scaleFactor;

        // Prevent division by zero
        if(modelDistance != 0)
            distanceError += fabs(objectDistance - modelDistance) / (modelDistance);
    }

    distanceError = distanceError / (double)lineMatchMap.size();

    positionRating = 1.0 - distanceError;
}

void Hypothesis::calculateScale()
{
    if(lineMatchMap.size() == 1){
        this->scaleFactor = (*lineMatchMap.begin()).first->getLength() / (*lineMatchMap.begin()).second->getLength();
        return;
    }

    double scale = 0;

    std::pair<cv::Point2d, cv::Point2d> centers = calculateCenters();

    for(auto lineMatch : lineMatchMap)
    {
            cv::Point2d LineCenterToObjectCenter = centers.first - lineMatch.first->getCenterPoint();
            double objectDistanceToCenter = cv::norm(LineCenterToObjectCenter);

            cv::Point2d LineCenterToModelCenter = centers.second - lineMatch.second->getCenterPoint();
            double modelDistanceToCenter = cv::norm(LineCenterToModelCenter);

           scale += objectDistanceToCenter / modelDistanceToCenter;
    }

    this->scaleFactor = scale / (double)lineMatchMap.size();
}

std::pair<cv::Point2d, cv::Point2d> Hypothesis::calculateCenters()
{
    unsigned int lineCount = 0;

    cv::Point2d objectLineSum;
    cv::Point2d modelLineSum;

    for(auto iter : lineMatchMap)
    {
        objectLineSum += iter.first->getCenterPoint();
        modelLineSum += iter.second->getCenterPoint();
        ++lineCount;
    }

    cv::Point2d objectCenter;
    objectCenter.x = objectLineSum.x / (double)lineCount;
    objectCenter.y = objectLineSum.y / (double)lineCount;

    for(auto line : notMatchingLines)
    {
        modelLineSum += line->getCenterPoint();
        ++lineCount;
    }

    cv::Point2d modelCenter;
    modelCenter.x = modelLineSum.x / (double)lineCount;
    modelCenter.y = modelLineSum.y / (double)lineCount;

    return std::make_pair(objectCenter, modelCenter);
}

const Model* Hypothesis::getModel() const
{
    return model;
}

const std::map<Line*, Line*> Hypothesis::getLineMatchMap() const
{
    return lineMatchMap;
}

void Hypothesis::addNotMatchingLines(const Line* line)
{
    notMatchingLines.push_back(line);
}

} // namespace formseher
