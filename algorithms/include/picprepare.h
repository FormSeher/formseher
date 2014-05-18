#ifndef PICTUREPREPARE_H
#define PICTUREPREPARE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

namespace formseher
{

class PicturePrepare
{
public:
    PicturePrepare();
    PicturePrepare(Mat src);

    Mat startPreparePicture();

private:
    Mat m_srcPic;

};

}
#endif // PICTUREPREPARE_H
