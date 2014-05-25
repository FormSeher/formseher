#include "objectdetection/object.h"

#include <sstream>

namespace formseher
{

Object::Object()
    : rating(0.0f)
{
}

Object::~Object()
{
    for(auto line : lines)
        delete line;
}

const std::vector<const Line*> &Object::getLines() const
{
    return lines;
}

cv::Rect Object::getBoundingBox() const
{
    return cv::Rect(
            boundingBoxCorners[0].x, // x
            boundingBoxCorners[0].y, // y
            boundingBoxCorners[1].x - boundingBoxCorners[0].x, // width
            boundingBoxCorners[1].y - boundingBoxCorners[0].y  // height
            );
}

void Object::addLine(const Line line)
{
    Line* newLine = new Line(line);
    lines.push_back(newLine);

    // update bounding box. First check is needed for the first inserted
    // corner of the bounding box.
    if(lines.size() == 1)
    {
        boundingBoxCorners[0] = newLine->getStart();
        boundingBoxCorners[1] = newLine->getEnd();
    }
    else
        updateBoundingBox(newLine->getStart());

    updateBoundingBox(newLine->getEnd());
}

void Object::setName(std::string name)
{
    this->name = name;
}

std::string Object::getName() const
{
    return name;
}

void Object::fromString(const std::string& string)
{
    // Set name
    size_t pos = string.find(':');
    size_t subPos;
    setName(string.substr(0, pos));

    std::string lineString;
    pos += 1;

    // Iterate through serialized lines (which are separated with semicolons)
    while((subPos = string.find(';', pos)) != std::string::npos)
    {
        // String of the 4 coordinates required to form a line
        lineString = string.substr(pos, subPos - pos);
        pos = subPos + 1;

        // Save where current coordinate starts and ends in string
        int coordinateStart = 0;
        int coordinateEnd = 0;
        // Used to convert string to int
        std::stringstream convertStream;
        // Coordinates of the start and end points
        int coordinates[4];

        // Iterate through the 4 coordinates
        for(int i = 0; i < 4; ++i)
        {
            coordinateEnd = lineString.find(',', coordinateStart);

            // Put string coordinate into converter
            convertStream.str(lineString.substr(coordinateStart, coordinateEnd - coordinateStart) + "\n");
            // Store the converted coordinate
            convertStream >> coordinates[i];

            // Move on to next coordinate
            coordinateStart = coordinateEnd + 1;
        }

        // Now create line with determined coordinates
        addLine(Line(coordinates[0], coordinates[1], coordinates[2], coordinates[3]));
    }
}

std::string Object::toString()
{
    std::stringstream serialized;

    // Serialize name
    serialized << getName();
    serialized << ":";

    // Serialize lines (start and end points)
    for(auto line : lines)
    {
        serialized << line->getStart().x << "," << line->getStart().y << ",";
        serialized << line->getEnd().x << "," << line->getEnd().y;
        serialized << ";";
    }

    return serialized.str();
}

void Object::setRating(float rating)
{
    this->rating = rating;
}

float Object::getRating()
{
    return rating;
}

void Object::updateBoundingBox(const cv::Point2i& point)
{
    // Update x coordinate
    if(boundingBoxCorners[0].x > point.x)
        boundingBoxCorners[0].x = point.x;
    else if(boundingBoxCorners[1].x < point.x)
        boundingBoxCorners[1].x = point.x;

    // Update y coordinate
    if(boundingBoxCorners[0].y > point.y)
        boundingBoxCorners[0].y = point.y;
    else if(boundingBoxCorners[1].y < point.y)
        boundingBoxCorners[1].y = point.y;
}

} // namespace formseher
