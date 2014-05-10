#ifndef OBJECTGRAPH_H
#define OBJECTGRAPH_H

#include <opencv2/core/core.hpp>

class ObjectGraph : public std::vector<cv::Point>
{
public:
    ObjectGraph();
};

#endif // OBJECTGRAPH_H
