#ifndef FS_OBJECTGRAPHEDGE_H
#define FS_OBJECTGRAPHEDGE_H

#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphnode.h"

namespace formseher
{

class ObjectGraphEdge : public cv::Vec2i
{
public:
    ObjectGraphEdge(const ObjectGraphNode& start, const ObjectGraphNode& end);

    int getDistance() const;

    bool operator==(const ObjectGraphEdge& rhs);
    bool operator!=(const ObjectGraphEdge& rhs);

    const ObjectGraphNode& getStart() const;
    const ObjectGraphNode& getEnd() const;

private:
    int distance;

    const ObjectGraphNode& start;
    const ObjectGraphNode& end;
};

} // namespace formseher

#endif // FS_OBJECTGRAPHEDGE_H
