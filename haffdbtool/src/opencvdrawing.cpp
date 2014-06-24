//#include "include/opencvdrawing.h"
//#include <opencv2/highgui/highgui.hpp>

//#include <iostream>
//using namespace std;

//OpencvDrawing::OpencvDrawing()
//{
//}



//std::vector<formseher::Line> OpencvDrawing::drawLines(cv::Mat image)
//{
//    startPoint.x = -1;
//    startPoint.y = -1;

//    //Create a window
//    cv::namedWindow("Image", 1);

//    //set the callback function for any mouse event
//    cv::setMouseCallback("Image", CallBackFunc, NULL);

//    //show the image
//    cv::imshow("Image", image);

//    // Wait until user press some key
//    cv::waitKey(0);

//}

//void CallBackFunc(int event, int x, int y, int flags, void* userdata)
//{
//    if  ( event == cv::EVENT_LBUTTONDOWN )
//    {
//        if ( OpencvDrawing::startPoint.x == -1 && OpencvDrawing::startPoint.y == -1 )
//        {
//            OpencvDrawing::startPoint.x = x;
//            OpencvDrawing::startPoint.y = y;
//            cout << "Startpoint: (" << x << ", " << y << ")" << endl;
//        }
//        else
//        {
//            OpencvDrawing::lineVector.push_back(formseher::Line(OpencvDrawing::startPoint.x, OpencvDrawing::startPoint.y, x, y));

//            OpencvDrawing::startPoint.x = -1;
//            OpencvDrawing::startPoint.y = -1;
//            cout << "Line: " << OpencvDrawing::startPoint << " → [" << x << ", " << y << "]" << endl;

//        }

//    }
//    else if  ( event == cv::EVENT_RBUTTONDOWN )
//    {
//        //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
//    }
//    else if ( event == cv::EVENT_MOUSEMOVE )
//    {
//        //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

//    }
//}
