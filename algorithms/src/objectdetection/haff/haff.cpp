#include "objectdetection/haff/haff.h"
#include "objectdetection/haff/hypothesis.h"

#include <set>

#include "pointercompare.h"

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
    std::multiset<Hypothesis*, PointerCompare<Hypothesis>> oldHypotheses;
    std::multiset<Hypothesis*, PointerCompare<Hypothesis>> newHypotheses;
    std::multiset<Hypothesis*, PointerCompare<Hypothesis>> likelyHypotheses;

    for(auto modelIter = databaseModels.begin(); modelIter != databaseModels.end(); ++modelIter)
    {
        Model* model = &(*modelIter);
        auto modelLineIter = model->getLines().begin();

        // Initialisation step
        for(auto detectedLinesIter = detectedLines.begin(); detectedLinesIter != detectedLines.end(); ++detectedLinesIter)
        {
            Line* detectedLine = &(*detectedLinesIter);

            if( *detectedLine == detectedLines.at(0) )
            {
                Hypothesis* newHypothesis = new Hypothesis(model, angleWeight, coverageWeight);
                newHypothesis->addNotMatchingLines(*modelLineIter);
                oldHypotheses.insert(newHypothesis);
            }

            Hypothesis* newHypothesis = new Hypothesis(model, angleWeight, coverageWeight);
            newHypothesis->addLineMatch(detectedLine, *modelLineIter);
            newHypothesis->calculateRating();
            oldHypotheses.insert(newHypothesis);

        }

         // Run iterations
        ++modelLineIter;
        for(; modelLineIter != model->getLines().end(); ++modelLineIter)
        {
            for(auto detectedLinesIter = detectedLines.begin(); detectedLinesIter != detectedLines.end(); ++detectedLinesIter)
            {
                Line* detectedLine = &(*detectedLinesIter);

                for(auto oldHypothesis : oldHypotheses)
                {
                    if ( ! oldHypothesis->containsLine( detectedLine ) )
                    {
                        if( *detectedLine == detectedLines.at(0) )
                        {
                            Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                            newHypothesis->addNotMatchingLines(*modelLineIter);
                            newHypotheses.insert(newHypothesis);
                        }

                        Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                        newHypothesis->addLineMatch(detectedLine, *modelLineIter);
                        newHypothesis->calculateRating();
                        newHypotheses.insert(newHypothesis);
                    }
                }
            } // FOREACH detectedline

            // Clear old hypotheses witch are no longer required
            for(auto oldHypothesis : oldHypotheses)
                delete oldHypothesis;
            oldHypotheses.clear();
            // Copy best rated new hypotheses to oldHyptoheses
            int counter = 0;

            std::multiset<Hypothesis*>::reverse_iterator itr;
            for(itr = newHypotheses.rbegin();
                itr != newHypotheses.rend() && counter < numberOfBestHypotheses;
                ++itr)
            {
                oldHypotheses.insert(*itr);
                ++counter;

            }

            // Delete rest of newHypotheses which is no longer needed
            for(; itr != newHypotheses.rend(); ++itr)
                delete *itr;
            newHypotheses.clear();

        } // FOREACH modelline

        std::multiset<Hypothesis*>::iterator itr;
        int counter = 0;
        for(itr = oldHypotheses.begin();
            itr != oldHypotheses.end() && counter < numberOfDetectedObjects;
            ++itr)
        {
            if ( (*itr)->getRating() < minimalObjectRating)
                break;

            likelyHypotheses.insert(*itr);
            ++counter;
        }

        int trimCounter = 0;
        for(itr = likelyHypotheses.begin();
            itr != likelyHypotheses.end();
            ++itr)
        {
            if(trimCounter >= numberOfDetectedObjects)
            {
                likelyHypotheses.erase(itr);
                delete *itr;
            }
            trimCounter++;
        }
    } // FOREACH model


    // Create Objects
    std::vector<Object> detectedObjects;
    std::multiset<Hypothesis*>::iterator itr;

    for(itr = likelyHypotheses.begin();
        itr != likelyHypotheses.end();
        ++itr)
    {
        Object tmp;
        tmp.setName((*itr)->getModel()->getName());
        tmp.setRating((double)(*itr)->getRating());
        for(auto lineMatch : (*itr)->getLineMatchMap())
        {
            tmp.addLine(*lineMatch.first);
        }
        detectedObjects.push_back(tmp);
    }

    return detectedObjects;
}

} // namespace formseher
