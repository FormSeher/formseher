#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

const double Hypothesis::angleWeight = 1.0;
const double Hypothesis::coverWeight = 1.0;
const double Hypothesis::scaleWeight = 1.0;

void Hypothesis::calculateRating()
{
    // Calculate angle rating

    // Calculate cover rating

    // Calculate scale rating
}

double Hypothesis::getRating() const
{
    return ( angleRating * angleWeight
           + coverRating * coverWeight
           + scaleRating * scaleWeight ) ;
}

bool Hypothesis::containsLine(const Line* line) const
{
    return ( lineMatchMap.find( (Line*) line ) != lineMatchMap.end() );
}

void Hypothesis::addLineMatch(const Line* pictureLine, const Line* databaseLine)
{
    lineMatchMap.insert( std::pair<Line*, Line*>((Line*)pictureLine, (Line*)databaseLine) );
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
    return 1.0d - (totalError / lineMatchMap.size());
}

} // namespace formseher
