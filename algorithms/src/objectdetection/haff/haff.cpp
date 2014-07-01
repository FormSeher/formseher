#include "objectdetection/haff/haff.h"
#include "objectdetection/haff/hypothesis.h"

#include <set>

#include "pointercompare.h"

namespace formseher {

Haff::Haff(int numberOfBestHypotheses, int numberOfDetectedObjects,
           double minimalObjectRating, double coverageWeight, double angleWeight, double positionWeight)
    : numberOfBestHypotheses(numberOfBestHypotheses),
      numberOfDetectedObjects(numberOfDetectedObjects),
      minimalObjectRating(minimalObjectRating),
      coverageWeight(coverageWeight),
      angleWeight(angleWeight),
      positionWeight(positionWeight)
{
}

std::vector<Object> Haff::calculate(std::vector<Line> detectedLines)
{
    if(detectedLines.size() < 5)
        return std::vector<Object>();

    std::multiset<Hypothesis*, PointerCompare<Hypothesis>> hypothesesVector1;
    std::multiset<Hypothesis*, PointerCompare<Hypothesis>> hypothesesVector2;
    auto oldHypotheses = &hypothesesVector1;
    auto newHypotheses = &hypothesesVector2;

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
                oldHypotheses->insert(newHypothesis);
            }

            Hypothesis* newHypothesis = new Hypothesis(model, angleWeight, coverageWeight);
            newHypothesis->addLineMatch(detectedLine, *modelLineIter);
            newHypothesis->calculateRating();
            oldHypotheses->insert(newHypothesis);
        }

         // Run iterations
        ++modelLineIter;
        for(; modelLineIter != model->getLines().end(); ++modelLineIter)
        {
            for(auto detectedLinesIter = detectedLines.begin(); detectedLinesIter != detectedLines.end(); ++detectedLinesIter)
            {
                Line* detectedLine = &(*detectedLinesIter);

                for(auto oldHypothesis : *oldHypotheses)
                {
                    if ( ! oldHypothesis->containsLine( detectedLine ) )
                    {
                        if( *detectedLine == detectedLines.at(0) )
                        {
                            Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                            newHypothesis->addNotMatchingLines(*modelLineIter);
                            newHypotheses->insert(newHypothesis);
                        }

                        Hypothesis* newHypothesis = new Hypothesis(*oldHypothesis);
                        newHypothesis->addLineMatch(detectedLine, *modelLineIter);
                        newHypothesis->calculateRating();
                        newHypotheses->insert(newHypothesis);
                    }
                }
            } // FOREACH detectedline

            // Clear old hypotheses witch are no longer required
            for(Hypothesis* oldHypothesis : *oldHypotheses)
            {
                delete oldHypothesis;
                oldHypothesis = nullptr;
            }
            oldHypotheses->clear();

            // Delete hypotheses no longer needed (number of hypotheses to delete == deletionCounter)
            size_t deletionCounter = newHypotheses->size() - numberOfBestHypotheses;
            auto itr = newHypotheses->begin();

            for(; deletionCounter > 0; --deletionCounter)
            {
                delete *itr;
                itr = newHypotheses->erase(itr);
            }

            // Swap pointers to hypothesis vectors
            std::swap(newHypotheses, oldHypotheses);

        } // FOREACH modelline

        int counter = 0;
        for(auto itr = oldHypotheses->rbegin();
            itr != oldHypotheses->rend() && counter < numberOfDetectedObjects;
            ++itr)
        {
            if ( (*itr)->getRating() < minimalObjectRating)
                break;

            likelyHypotheses.insert(*itr);
            oldHypotheses->erase(--itr.base());
            ++counter;
        }

        // Clear oldHypotheses
        for(Hypothesis* oldHypothesis : *oldHypotheses)
            delete oldHypothesis;
        oldHypotheses->clear();
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

        suppressedInsertion(detectedObjects, tmp);

        // Delete hypothesis
        delete *itr;
    }
    likelyHypotheses.clear();

    return detectedObjects;
}

void Haff::suppressedInsertion(std::vector<Object>& detectedObjects, Object& object)
{
    // Environment is 2^environmentExponent. 2^x can be better optimized with shifting.
    short environmentExponent = 4;

    cv::Rect objectBoundingBox = object.getBoundingBox();
    cv::Point2i objectCenter;
    objectCenter.x = (objectBoundingBox.x + ( objectBoundingBox.width >> 1)) >> environmentExponent;
    objectCenter.y = (objectBoundingBox.y + ( objectBoundingBox.height >> 1)) >> environmentExponent;

    // Check if there is an object with the same Center (in the environment range).
    // If there is, then compare the ratings. If it's lower than discard the object otherwise replace the saved object.
    for(size_t counter = 0; counter < detectedObjects.size(); counter++)
    {
        cv::Rect detectedBoundingBox = detectedObjects.at(counter).getBoundingBox();
        cv::Point2i detectedCenter;
        detectedCenter.x = (detectedBoundingBox.x + ( detectedBoundingBox.width >> 1)) >> environmentExponent;
        detectedCenter.y = (detectedBoundingBox.y + ( detectedBoundingBox.height >> 1)) >> environmentExponent;

        // Supress objects with same center point
        if(objectCenter == detectedCenter)
        {
            if( object.getRating() >= detectedObjects.at(counter).getRating() )
            {
                detectedObjects.at(counter) = object;
                return;
            }
            else
                return;
        }

        // Supress objects whose bounding boxes intersect
        if( objectBoundingBox.x < (detectedBoundingBox.x + detectedBoundingBox.width)
         && (objectBoundingBox.x + detectedBoundingBox.width) > detectedBoundingBox.x
         && objectBoundingBox.y < (detectedBoundingBox.y + detectedBoundingBox.height)
         && (objectBoundingBox.y + detectedBoundingBox.height) > detectedBoundingBox.y)
        {
            if( object.getRating() >= detectedObjects.at(counter).getRating() )
            {
                detectedObjects.at(counter) = object;
                return;
            }
            else
                return;
        }

        // Supress objects that would use the same lines.
        else
        {
            for( const Line* detectedObjectLine : detectedObjects.at(counter).getLines())
            {
                for( const Line* objectLine : object.getLines() )
                {
                    if( detectedObjectLine == objectLine )
                    {
                        if( object.getRating() >= detectedObjects.at(counter).getRating() )
                        {
                            detectedObjects.at(counter) = object;
                            return;
                        }
                        else
                            return;
                    }
                }
            }
        }
    }

    detectedObjects.push_back(object);
}

} // namespace formseher
