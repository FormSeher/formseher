#ifndef FS_OBJECTGRAPHEDGE_H
#define FS_OBJECTGRAPHEDGE_H

#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphnode.h"

namespace formseher
{

class ObjectGraphEdge
{
public:
    ObjectGraphEdge(ObjectGraphNode& start, ObjectGraphNode& end);

    int getDistance() const;

    bool operator==(const ObjectGraphEdge& rhs);
    bool operator!=(const ObjectGraphEdge& rhs);

    ObjectGraphNode& getStart() const;
    ObjectGraphNode& getEnd() const;

    cv::Vec2i toCvVector() const;

private:
    cv::Vec2i vector;

    int distance;

    ObjectGraphNode& start;
    ObjectGraphNode& end;
};

} // namespace formseher

#endif // FS_OBJECTGRAPHEDGE_H
