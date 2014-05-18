#ifndef FS_OBJECTGRAPHVISUALIZER_H
#define FS_OBJECTGRAPHVISUALIZER_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class ObjectGraph;

class ObjectGraphVisualizer
{
public:
    ObjectGraphVisualizer();

    static void drawGraphOnMatrix(const ObjectGraph* graph, cv::OutputArray matrix);
};

} // namespace formseher
#endif // FS_OBJECTGRAPHVISUALIZER_H
