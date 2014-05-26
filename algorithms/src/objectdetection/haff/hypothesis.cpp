#include "objectdetection/haff/hypothesis.h"

namespace formseher
{

const double Hypothesis::angleFactor = 1.0;
const double Hypothesis::coverFactor = 1.0;
const double Hypothesis::scaleFactor = 1.0;

void Hypothesis::calculateRating()
{
    // Calculate angle rating

    // Calculate cover rating

    // Calculate scale rating
}

double Hypothesis::getRating() const
{
    return ( angleRating * angleFactor
           + coverRating * coverFactor
           + scaleRating * scaleFactor ) ;
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
