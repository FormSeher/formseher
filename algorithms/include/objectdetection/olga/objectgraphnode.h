#ifndef OBJECTGRAPHNODE_H
#define OBJECTGRAPHNODE_H

#include <opencv2/core/core.hpp>
#include <vector>

//#include "objectdetection/olga/objectgraphedge.h"
class ObjectGraphEdge;

class ObjectGraphNode : public cv::Point2i
{
public:
    ObjectGraphNode(int x, int y);

private:
    std::vector<ObjectGraphEdge*> edges;
};

#endif // OBJECTGRAPHNODE_H
