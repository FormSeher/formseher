#ifndef FS_OBJECTGRAPHNODE_H
#define FS_OBJECTGRAPHNODE_H

#include <opencv2/core/core.hpp>
#include <vector>

namespace formseher
{

//#include "objectdetection/olga/objectgraphedge.h"
class ObjectGraphEdge;

class ObjectGraphNode : public cv::Point2i
{
public:
    ObjectGraphNode(int x, int y);

    void addEdge(const ObjectGraphEdge* edge);
    const std::vector<const ObjectGraphEdge*>& getEdges() const;

    bool operator<(const ObjectGraphNode& rhs) const;

private:
    std::vector<const ObjectGraphEdge*> edges;
};

} // namespace formseher

#endif // FS_OBJECTGRAPHNODE_H
