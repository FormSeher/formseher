#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

ObjectDetectionAlgorithm::ObjectDetectionAlgorithm()
{
}

virtual std::vector<Object*> ObjectDetectionAlgorithm::calculate(std::vector<Line> lines){

    Line firstLine;
    Line secondLine;

    // iterate through received line vector
    // first step: every line equals the first line of a object
    for(uint firstLineIndex = 0; firstLineIndex < lines.size(); firstLineIndex++){

        firstLine = lines[firstLineIndex];

        // second step: match firstLine with all other lines which equal the second line of a object
        for(uint secondLineIndex = 0; secondLineIndex < lines.size(); secondLineIndex++){

        // shorter iteration if comparison between first and second line only needs an angle
        // if relative sizes between lines have to be considered this loop cannot be used
        // for(uint secondLineIndex = firstLineIndex; secondLineIndex < lines.size(); secondLineIndex++){

            // skip same line
            if(firstLineIndex == secondLineIndex){
                continue;
            }

            secondLine = lines[secondLineIndex];

        }
    }
}

} // namespace formseher
