// Database tool
#include "opencvdrawing.h"

// OpenCV
#include <opencv2/highgui/highgui.hpp>

cv::Point2i OpencvDrawing::startPoint;
std::vector<formseher::Line> OpencvDrawing::lineVector;
cv::Mat OpencvDrawing::resultImage;

OpencvDrawing::OpencvDrawing()
{
}

std::vector<formseher::Line> OpencvDrawing::drawLines(cv::Mat image)
{
    OpencvDrawing::resultImage = image.clone();

    OpencvDrawing::startPoint.x = -1;
    OpencvDrawing::startPoint.y = -1;

    lineVector.clear();

    //Create a window
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);

    //set the callback function for any mouse event
    cv::setMouseCallback("Image", CallBackFunc, &image);

    //show the image
    cv::imshow("Image", resultImage);

    // Wait until user press some key
    cv::waitKey(0);

    return lineVector;
}

void OpencvDrawing::CallBackFunc(int event, int x, int y, int flags, void* image)
{
    cv::Mat img = *((cv::Mat*) image);
    resultImage = img.clone();

    for(formseher::Line line : lineVector)
    {
        cv::line(resultImage, line.getStart(), line.getEnd(), cv::Scalar(80, 120, 230), 2);
    }

    if ( event == cv::EVENT_LBUTTONDOWN && flags != cv::EVENT_FLAG_CTRLKEY )
    {
        if ( startPoint.x == -1 && startPoint.y == -1 )
        {
            startPoint.x = x;
            startPoint.y = y;
        }
        else
        {
            lineVector.push_back(formseher::Line(startPoint.x, startPoint.y, x, y));
            startPoint.x = -1;
            startPoint.y = -1;
        }
    }
    else if ( event == cv::EVENT_MBUTTONDOWN )
    {
        startPoint.x = -1;
        startPoint.y = -1;
    }
    else if ( event == cv::EVENT_MOUSEMOVE )
    {
        if( ! ( startPoint.x == -1 && startPoint.y == -1 ) )
        {
            cv::line(resultImage, startPoint, cv::Point2i(x,y), cv::Scalar(80, 190, 240), 2);
        }
    }

    imshow("Image", resultImage);
}
