#ifndef FS_HYPOTHESIS_H
#define FS_HYPOTHESIS_H

#include "objectdetection/object.h"

namespace formseher
{

class Hypothesis
{
public:
    void calculateRating();

    double getRating() const;

    bool containsLine(const Line* line) const;

    void addLineMatch(const Line *pictureLine, const Line *databaseLine);

    bool operator<(const Hypothesis& hypo) const;
    	
private:
    /**
     * @brief Calculates rating of angles.
     * @return Rating of angle match between 0 (0% match) and 1 (100% match).
     */
    double calculateAngleRating();

    double angleRating;
    double coverRating;
    double scaleRating;

    static const double angleFactor;
    static const double coverFactor;
    static const double scaleFactor;

    //<PictureLine, DB-Line>
    std::map<Line*, Line*> lineMatchMap;
    
    const Object* object;

};

}   // namespace formseher

#endif // FS_HYPOTHESIS_H
