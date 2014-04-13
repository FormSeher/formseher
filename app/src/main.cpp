//#include <mainwindow.h>
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

#include <mainwindow.h>

#include <QApplication>
#include <iostream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "edl/edl.h"
#include "line.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "Call with path to an image file!" << std::endl;
        return 0;
    }

    cv::Mat input = cv::imread(argv[1]);

    if(!input.data)
    {
        std::cerr << "Invalid input file. Must be an image!" << std::endl;
        std::cerr << "Could not load image '" << argv[1] << "'!" << std::endl;
        return -1;
    }

    EDL edl;
    edl.setInput(argv[1]);
    edl.calculate();

    std::vector<Line*>* result = edl.getResult();
    std::cout << "lines found: " << result->size() << std::endl;

    int color = 30;
    for(auto line : *result)
    {
        cv::line(input, line->getStart(), line->getEnd(), cv::Scalar(color,0,255), 1);
        color += 30;
        delete line;
    }
    delete result;

    cv::imshow("result", input);

    cv::waitKey(0);
    return 0;
}
