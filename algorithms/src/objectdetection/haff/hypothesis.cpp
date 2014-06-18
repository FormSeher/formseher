#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

Hypothesis::Hypothesis(const Model *model, double angleWeight, double coverWeight)
    : model(model),
      angleWeight(angleWeight),
      coverWeight(coverWeight)
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

}

Hypothesis::Hypothesis(const Hypothesis& hypothesis)
    : model(hypothesis.model),
      angleWeight(hypothesis.angleWeight),
      coverWeight(hypothesis.coverWeight),
      lineMatchMap(hypothesis.lineMatchMap),
      notMatchingLines(hypothesis.notMatchingLines)
{
}

double Hypothesis::getRating() const
{
    return ( angleRating * angleWeight
           + coverRating * coverWeight ) * 100.0;
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
	double ownRating = getRating();
	double foreignRating = hypo.getRating();
	
    if(ownRating < foreignRating)
	{
		return true;
	}
    else return false;
}

double Hypothesis::calculateAngleRating()
{
    if(lineMatchMap.size() < 2)
        return 1.0;

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
    return 1.0d - (totalError / (double)lineMatchMap.size());
}

void Hypothesis::calculateCoverageRating()
{
    double coverageRaiting = 0.0;
    double endPointCoverageRaiting = 0.0;
    double startPointCoverageRaiting = 0.0;

    std::pair<cv::Point2d, cv::Point2d> centers = calculateCenters();

    for(auto lineMatch : lineMatchMap)
    {

        //vektor von modelmittelpunkt zum linienmittelpunk

        cv::Point2d vectorFromModelCenterToLineCenter = lineMatch.first->getCenterPoint() - centers.first;


        //vector mal scale  mit dem dann vom objektMTLP

        vectorFromModelCenterToLineCenter.x *= scaleFactor;
        vectorFromModelCenterToLineCenter.y *= scaleFactor;

        //von dem Punkt zum start und endpunkt
        cv::Point2d hypotheticleObjectLineCenter = centers.second + vectorFromModelCenterToLineCenter;

        cv::Vec2d ObjectDistanceToStart;
        ObjectDistanceToStart[0] = (double)lineMatch.second->getStart().x - hypotheticleObjectLineCenter.x;
        ObjectDistanceToStart[1] = (double)lineMatch.second->getStart().y - hypotheticleObjectLineCenter.y;
        cv::Vec2d ObjectDistanceToEnd;
        ObjectDistanceToEnd[0] = (double)lineMatch.second->getEnd().x - hypotheticleObjectLineCenter.x;
        ObjectDistanceToEnd[1] = (double)lineMatch.second->getEnd().y - hypotheticleObjectLineCenter.y;

        cv::Vec2d ModelDistanceToStart;
        ModelDistanceToStart[0] = (double)lineMatch.first->getStart().x - lineMatch.first->getCenterPoint().x;
        ModelDistanceToStart[1] = (double)lineMatch.first->getStart().y - lineMatch.first->getCenterPoint().y;
        cv::Vec2d ModelDistanceToEnd;
        ModelDistanceToEnd[0] = (double)lineMatch.first->getEnd().x - lineMatch.first->getCenterPoint().x;
        ModelDistanceToEnd[1] = (double)lineMatch.first->getEnd().y - lineMatch.first->getCenterPoint().y;


        startPointCoverageRaiting = cv::norm(ObjectDistanceToStart) * scaleFactor
                                    / cv::norm(ModelDistanceToStart);

        endPointCoverageRaiting = cv::norm(ObjectDistanceToEnd) * scaleFactor
                                  / cv::norm(ModelDistanceToEnd);

        if(startPointCoverageRaiting > 1)
        {
            startPointCoverageRaiting = 1;
        }

        if(endPointCoverageRaiting > 1)
        {
            endPointCoverageRaiting = 1;

        }
        coverageRaiting += ((startPointCoverageRaiting + endPointCoverageRaiting) / 2.0);
    }

    this->coverRating =  coverageRaiting / (double)lineMatchMap.size();
}

void Hypothesis::calculateScale()
{
    double scale = 0;

    std::pair<cv::Point2d, cv::Point2d> centers = calculateCenters();

    if(lineMatchMap.size() == 1){
        this->scaleFactor = (*lineMatchMap.begin()).first->getLength() / (*lineMatchMap.begin()).second->getLength();
        return;
    }

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
