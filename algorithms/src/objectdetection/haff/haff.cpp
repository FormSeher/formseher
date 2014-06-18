#include "objectdetection/haff/haff.h"
#include "objectdetection/haff/hypothesis.h"

#include <set>

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
            for(auto detectedLine : detectedLines)
            {
                if ( modelLine == model.getLines().front() )
                {
                    if( detectedLine == detectedLines.at(0) )
                    {
                        Hypothesis* newHypothesis = new Hypothesis(&model, angleWeight, coverageWeight);
                        newHypothesis->addNotMatchingLines(modelLine);
                        newHypotheses.insert(newHypothesis);
                    }

                    Hypothesis* newHypothesis = new Hypothesis(&model, angleWeight, coverageWeight);
                    newHypothesis->addLineMatch(&detectedLine, modelLine);
                    newHypothesis->calculateRating();
                    newHypotheses.insert(newHypothesis);
                }

                else
                {
                    for(auto oldHypothesis : oldHypotheses)
                    {
                        if ( ! oldHypothesis->containsLine( &detectedLine ) )
                        {
                            if( detectedLine == detectedLines.at(0) )
                            {
                                Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                                newHypothesis->addNotMatchingLines(modelLine);
                                newHypotheses.insert(newHypothesis);
                            }

                            Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                            newHypothesis->addLineMatch(&detectedLine, modelLine);
                            newHypothesis->calculateRating();
                            newHypotheses.insert(newHypothesis);
                        }
                    }
                }

            } // FOREACH detectedline

            // Clear old hypotheses witch are no longer required
            for(auto oldHypothesis : oldHypotheses)
                delete oldHypothesis;
            oldHypotheses.clear();
            // Copy best rated new hypotheses to oldHyptoheses
            int counter = 0;

            std::multiset<Hypothesis*>::iterator itr;
            for(itr = newHypotheses.begin();
                itr != newHypotheses.end() && counter < numberOfBestHypotheses;
                ++itr)
            {
                oldHypotheses.insert(*itr);
                ++counter;

            }

            // Delete rest of newHypotheses which is no longer needed
            for(; itr != newHypotheses.end(); ++itr)
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
