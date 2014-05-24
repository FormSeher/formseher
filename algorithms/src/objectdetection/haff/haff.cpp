#include "objectdetection/haff/haff.h"

#include <set>

#include "objectdetection/haff/hypothesis.h"

namespace formseher {

Haff::Haff(const HaffDatabase& database)
    : database(database)
{
}

std::vector<Object*> Haff::calculate(std::vector<Line> detectedLines)
{
    std::multiset<Hypothesis> oldHypotheses;
    std::multiset<Hypothesis> newHypotheses;

    for(auto model : database.getObjects())
    {
        for(auto modelLine : model->getLines())
        {
            for(auto detectedLine : detectedLines)
            {
                for(auto oldHypothesis : oldHypotheses)
                {
                    // Create new Hypothesis
                    // Rate new Hypothesis
                    // Store new Hypothesis in newHypotheses set
                }
            }

            // Filter newHypotheses for best ones (do not forget to destory
            // old hypohteses and new hypotheses which are no longer used!)
        }
    }

    std::vector<Object*> detectedObjects;
    return detectedObjects;
}

} // namespace formseher
