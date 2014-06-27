#ifndef OPENCVDRAWING_H
#define OPENCVDRAWING_H

#include "line.h"

class OpencvDrawing
{
public:
    OpencvDrawing();

    static std::vector<formseher::Line> drawLines(cv::Mat image);

private:
    static cv::Point2i startPoint;

    static std::vector<formseher::Line> lineVector;

    static cv::Mat resultImage;

    static void CallBackFunc(int event, int x, int y, int flags, void* image);
};

#endif // OPENCVDRAWING_H
