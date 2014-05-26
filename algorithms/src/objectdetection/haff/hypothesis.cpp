#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

const double Hypothesis::angleFactor = 1.0;
const double Hypothesis::coverFactor = 1.0;
const double Hypothesis::scaleFactor = 1.0;

void Hypothesis::calculateRating()
{

}

double Hypothesis::getRating() const
{
    return 0.0;
}

bool Hypothesis::containsLine(const Line* line) const
{
    return ( lineMatchMap.find( (Line*) line ) != lineMatchMap.end() );
}

void Hypothesis::addLineMatch(Line* pictureLine, Line* databaseLine)
{
    lineMatchMap.insert( std::pair<Line*, Line*>(pictureLine, databaseLine) );
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
} // namespace formseher
