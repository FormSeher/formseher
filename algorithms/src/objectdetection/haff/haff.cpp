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
    std::multiset<Hypothesis*> oldHypotheses;
    std::multiset<Hypothesis*> newHypotheses;
    std::multiset<Hypothesis*> likelyHypotheses;

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
                    Hypothesis* newHypothesis = new Hypothesis();
                    newHypothesis->addLineMatch(&detectedLine, modelLine);

                    // Rate new Hypothesis
                    newHypothesis->calculateRating();

                    // Store new Hypothesis in newHypotheses set
                    newHypotheses.insert(newHypothesis);
                }

                // Construct newHypotheses in other iteration steps.
                else
                {
                    for(auto oldHypothesis : oldHypotheses)
                    {
                        if ( ! oldHypothesis->containsLine( &detectedLine ) )
                        {
                            // TODO: Create a copy of oldHypothesis

                            // Create new Hypothesis
                            oldHypothesis->addLineMatch(&detectedLine, modelLine);

                            // Rate new Hypothesis
                            oldHypothesis->calculateRating();

                            // Store new Hypothesis in newHypotheses set
                            newHypotheses.insert(oldHypothesis);
                        }
                    }
                }

                // Clear old hypotheses witch are no longer required
                for(auto oldHypothesis : oldHypotheses)
                    delete oldHypothesis;
                oldHypotheses.clear();

                // Copy best rated new hypotheses to oldHyptoheses
                int counter = 0;
                std::multiset<Hypothesis*>::iterator itr;
                for(itr = newHypotheses.begin();
                    itr != newHypotheses.end() && counter < 10;
                    ++itr)
                {
                    oldHypotheses.insert(*itr);
                    ++counter;
                }

                // Delete rest of newHypotheses which is no longer needed
                for(; itr != newHypotheses.end(); ++itr)
                    delete *itr;
                newHypotheses.clear();
            }
        }

        // TODO: Add likliest hypothesis to likelyHyptohesis set.
    }

    std::vector<Object*> detectedObjects;

    // Create Objects

    return detectedObjects;
}

} // namespace formseher
