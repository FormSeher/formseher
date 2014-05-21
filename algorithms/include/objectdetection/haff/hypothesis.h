#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include "objectdetection/object.h"

namespace formseher
{

class Hypothesis
{
public:
    void calculateRating();
    double getRating() const;
    bool containsLine(const Line* line) const;

private:
    double angleRating;
    double coverRating;
    double scaleRating;

    static const double angleFactor = 1.0;
    static const double coverFactor = 1.0;
    static const double scaleFactor = 1.0;

    //<PictureLine, DB-Line>
    std::map<Line*, Line*> lineMatchMap;
    
    const Object* object;

};

}   // namespace formseher

#endif HYPOTHESIS_H
