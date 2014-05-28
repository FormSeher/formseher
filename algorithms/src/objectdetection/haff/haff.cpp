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
    std::multiset<Hypothesis> likelyHypotheses;

    for(auto model : database.getObjects())
    {
        for(auto modelLine : model->getLines())
        {
            // TODO: Clearify how to construct a "non-matching" hypothesis value-key pair?

            // Hypothesis h;
            // h.addLineMatch(0, modelLine);
            // h.calculateRating()
            // newHypotheses.insert(h);

            for(auto detectedLine : detectedLines)
            {
                // TODO: Ugly code duplication. How to improve?

                // Construct newHypotheses in first iteration step.
                if ( modelLine == model->getLines().front() )
                {
                    // Create new Hypothesis
                    Hypothesis newHypothesis = Hypothesis();
                    newHypothesis.addLineMatch(&detectedLine, modelLine);

                    // Rate new Hypothesis
                    newHypothesis.calculateRating();

                    // Store new Hypothesis in newHypotheses set
                    newHypotheses.insert(newHypothesis);
                }

                // Construct newHypotheses in other iteration steps.
                else
                {
                    for(auto oldHypothesis : oldHypotheses)
                    {
                        if ( ! oldHypothesis.containsLine( &detectedLine ) )
                        {
                            // TODO: Create a copy of oldHypothesis

                            // Create new Hypothesis
                            oldHypothesis.addLineMatch(&detectedLine, modelLine);

                            // Rate new Hypothesis
                            oldHypothesis.calculateRating();

                            // Store new Hypothesis in newHypotheses set
                            newHypotheses.insert(oldHypothesis);
                        }
                    }
                }

                // Filter newHypotheses for best ones (do not forget to destory
                // old hypohteses and new hypotheses which are no longer used!)
            }
        }

        // TODO: Add likliest hypothesis to likelyHyptohesis set.
    }

    std::vector<Object*> detectedObjects;

    // Create Objects

    return detectedObjects;
}

} // namespace formseher
