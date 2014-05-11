#ifndef OBJECTGRAPHEDGE_H
#define OBJECTGRAPHEDGE_H

#include <opencv2/core/core.hpp>

#include "objectdetection/olga/objectgraphnode.h"

class ObjectGraphEdge : public cv::Vec2i
{
public:
    ObjectGraphEdge(const ObjectGraphNode& start, const ObjectGraphNode& end);

    int getDistance() const;

private:
    int distance;
};

#endif // OBJECTGRAPHEDGE_H
