#ifndef FS_HYPOTHESIS_H
#define FS_HYPOTHESIS_H

#include "objectdetection/object.h"

namespace formseher
{

class Hypothesis
{
public:
    Hypothesis(double angleWeight = 1.0, double coverWeight = 1.0);

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

    /**
     * @brief The scaling of the object related to the matching object.
     */
    double scaleFactor;

    double angleRating;
    double coverRating;

    /**
     * @brief Factor with which the angleRating is weighted.
     */
    const double angleWeight;

    /**
     * @brief Factor with which the coverRating is weighted.
     */
    const double coverWeight;

    //<PictureLine, DB-Line>
    std::map<Line*, Line*> lineMatchMap;
    
    const Object* object;

};

}   // namespace formseher

#endif // FS_HYPOTHESIS_H
