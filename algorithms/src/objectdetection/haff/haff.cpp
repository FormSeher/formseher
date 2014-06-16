#include "objectdetection/haff/haff.h"

#include <set>

#include "objectdetection/haff/hypothesis.h"

namespace formseher {

Haff::Haff(int numberOfBestHypotheses, int numberOfDetectedObjects,
           double minimalObjectRating, double coverageWeight, double angleWeight)
    : numberOfBestHypotheses(numberOfBestHypotheses),
      numberOfDetectedObjects(numberOfDetectedObjects),
      minimalObjectRating(minimalObjectRating),
      coverageWeight(coverageWeight),
      angleWeight(angleWeight)
{
}

std::vector<Object> Haff::calculate(std::vector<Line> detectedLines)
{
    std::multiset<Hypothesis*> oldHypotheses;
    std::multiset<Hypothesis*> newHypotheses;
    std::multiset<Hypothesis*> likelyHypotheses;

    for(auto model : databaseModels)
    {
        for(auto modelLine : model.getLines())
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
                if ( modelLine == model.getLines().front() )
                {
                    // Create new Hypothesis
                    Hypothesis* newHypothesis = new Hypothesis(&model);
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
        std::multiset<Hypothesis*>::iterator itr;
        int counter = 0;
        for(itr = oldHypotheses.begin();
            itr != oldHypotheses.end() && counter < 10;
            ++itr)
        {
            likelyHypotheses.insert(*itr);
            ++counter;
        }

        int trimCounter = 0;
        for(itr = likelyHypotheses.begin();
            itr != likelyHypotheses.end();
            ++itr)
        {
            if(trimCounter >= 10)
            {
                likelyHypotheses.erase(itr);
                delete *itr;
            }
            trimCounter++;
        }

        // TODO: Add likliest hypothesis to likelyHyptohesis set.
    }

    std::vector<Object> detectedObjects;
    std::multiset<Hypothesis*>::iterator itr;

    for(itr = likelyHypotheses.begin();
        itr != likelyHypotheses.end();
        ++itr)
    {
        Object tmp;
        tmp.setName((*itr)->getModel()->getName());
        tmp.setRating((*itr)->getRating());
        for(auto lineMatch : (*itr)->getLineMatchMap())
        {

            tmp.addLine(*lineMatch.first);
        }

        detectedObjects.push_back(tmp);
    }
    // Create Objects

    return detectedObjects;
}

} // namespace formseher
