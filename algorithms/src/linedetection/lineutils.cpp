#include "linedetection/lineutils.h"
#include "line.h"

namespace formseher
{

std::vector<Line> LineUtils::combineLines(std::vector<Line> lineList)
{
std::vector<Line> result;

double perpendicularDistanceThreshold = 10.0;
double directionVectorAngleThreshold = 0.85;
double maximumDistanceThreshold = 20.0;

for(auto line1 : lineList)
{
    for(auto line2: lineList)
    {
        //Schritt 1 lotfußpunkt länge vergleichen (muss im treshold liegen)
        //Schritt 2 Vergleich der Richtungsvektoren über das Skalarprodukt (muss nahe 1 liegen)
        //Schritt zwei meine Vektoren vergleichen
        //hat einer der kleinste Vektoren eine minimale Länge unterschritten ist es ein match!
        //wenn Skalarprodukt SS und ES negativ ist liegt der Punkt zwischen start und endpunkt der linie1-> passt also
        // gleiches geht für SE und EE

        if(std::fabs(line1.getPerpendicularDistanceToOrigin() - line2.getPerpendicularDistanceToOrigin()) <= perpendicularDistanceThreshold)
        {
            if(std::fabs(line1.getDirectionVector().dot(line2.getDirectionVector())) >= directionVectorAngleThreshold)
            {
                cv::Vec2i SS; // from Start to Start
                SS[0] = line1.getStart().x - line2.getStart().x;
                SS[1] = line1.getStart().y - line2.getStart().y;

                cv::Vec2i SE; // from Start to End
                SS[0] = line1.getStart().x - line2.getEnd().x;
                SS[1] = line1.getStart().y - line2.getEnd().y;

                cv::Vec2i ES; // from End to Start
                SS[0] = line1.getEnd().x - line2.getStart().x;
                SS[1] = line1.getEnd().y - line2.getStart().y;

                cv::Vec2i EE; // from End to End
                SS[0] = line1.getEnd().x - line2.getEnd().x;
                SS[1] = line1.getEnd().y - line2.getEnd().y;
                if(norm(SS) <= maximumDistanceThreshold || norm(SE) <= maximumDistanceThreshold ||
                   norm(ES) <= maximumDistanceThreshold || norm(EE) <= maximumDistanceThreshold)
                {

                    cv::Point2i newStart;
                    cv::Point2i newEnd;

                    double normSS = norm(SS);
                    double normSE = norm(SE);
                    double normES = norm(ES);
                    double normEE = norm(EE);
                    double length1 = line1.getLength();
                    double length2 = line2.getLength();

                    if(normSS > normSE && normSS > normES && normSS > normEE && normSS > length1 && normSS > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line2.getStart();
                    }
                    else if(normSE > normSS && normSE > normES && normSE > normSE && normEE > length1 && normSE > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line2.getEnd();
                    }
                    else if(normES > normSS && normES > normSE && normES > normEE && normES > length1 && normES > length2)
                    {
                        newStart = line1.getEnd();
                        newEnd = line2.getStart();
                    }
                    else if(normEE > normSS && normEE > normSE && normEE > normES && normEE > length1 && normEE > length2)
                    {
                        newStart = line1.getEnd();
                        newEnd = line2.getEnd();
                    }
                    else if(length1 > normSS && length1 > normSE && length1 > normES && length1 > normEE && length1 > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line1.getEnd();
                    }
                    else if(length2 > normSS && length2 > normSE && length2 > normES && length2 > normEE && length2 > length1)
                    {
                        newStart = line2.getStart();
                        newEnd = line2.getEnd();
                    }

                    Line combinedLine = Line(newStart,newEnd);
                    result.push_back(combinedLine);
                }

                else if(SS.dot(ES) <= 0 || SE.dot(EE) <= 0)
                {
                    cv::Point2i newStart;
                    cv::Point2i newEnd;

                    double normSS = norm(SS);
                    double normSE = norm(SE);
                    double normES = norm(ES);
                    double normEE = norm(EE);
                    double length1 = line1.getLength();
                    double length2 = line2.getLength();

                    if(normSS > normSE && normSS > normES && normSS > normEE && normSS > length1 && normSS > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line2.getStart();
                    }
                    else if(normSE > normSS && normSE > normES && normSE > normSE && normEE > length1 && normSE > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line2.getEnd();
                    }
                    else if(normES > normSS && normES > normSE && normES > normEE && normES > length1 && normES > length2)
                    {
                        newStart = line1.getEnd();
                        newEnd = line2.getStart();
                    }
                    else if(normEE > normSS && normEE > normSE && normEE > normES && normEE > length1 && normEE > length2)
                    {
                        newStart = line1.getEnd();
                        newEnd = line2.getEnd();
                    }
                    else if(length1 > normSS && length1 > normSE && length1 > normES && length1 > normEE && length1 > length2)
                    {
                        newStart = line1.getStart();
                        newEnd = line1.getEnd();
                    }
                    else if(length2 > normSS && length2 > normSE && length2 > normES && length2 > normEE && length2 > length1)
                    {
                        newStart = line2.getStart();
                        newEnd = line2.getEnd();
                    }

                    Line combinedLine = Line(newStart,newEnd);
                    result.push_back(combinedLine);

                }
            }
        }

    } //for line2

} //for line1
}

} // namespace formseher
