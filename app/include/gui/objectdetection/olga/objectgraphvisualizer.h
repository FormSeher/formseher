#ifndef FS_OBJECTGRAPHVISUALIZER_H
#define FS_OBJECTGRAPHVISUALIZER_H

#include <opencv2/core/core.hpp>

namespace formseher
{

class ObjectGraph;

class ObjectGraphVisualizer
{
public:
    /**
     * @brief ObjectGraphVisualizer standard constructor.
     */
    ObjectGraphVisualizer();

    /**
     * @brief Draws given graph to given matrix.
     * @param graph ObjectGraph to be drawn.
     * @param matrix Matrix graph is drawn onto.
     */
    static void drawGraphOnMatrix(const ObjectGraph* graph, cv::OutputArray matrix);
};

} // namespace formseher
#endif // FS_OBJECTGRAPHVISUALIZER_H
