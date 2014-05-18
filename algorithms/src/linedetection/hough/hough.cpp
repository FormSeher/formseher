#include "linedetection/hough/hough.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

namespace formseher
{

Hough::Hough(u_int16_t checkEnvironmentSize, u_int16_t maximalLineGap, u_int16_t minimumLineSize)
    : checkEnvironmentSize(checkEnvironmentSize),
      maximalLineGap(maximalLineGap),
      minimumLineSize(minimumLineSize)
{
}

Hough::~Hough()
{
}

std::vector<Line> Hough::calculate(cv::InputArray _image)
{
    cv::Mat image = _image.getMat();
    std::vector<Line> result;
    cv::vector<cv::Vec2f> lines;

    if(!image.data)
        return result;

    imageDiagonal = sqrt( pow(image.rows, 2) + pow(image.cols, 2));

    cv::Mat cannyImage;

    getCannyImage(cannyImage, image);

    HoughLines(cannyImage, lines, 1, M_PI/180, minimalHoughVotes);

    compareHoughLinesWithCannyEdges(result, lines, cannyImage);

    return result;
}

bool Hough::checkEnvironmentInRightAngle(cv::Mat& inputMatrix, double currX, double currY)
{
    Point2i tmp;

    for( int i = 0 ; i < checkEnvironmentSize; i++ ){

//        tmp.x =    currX + i * lineDirection[1];
//        tmp.y =   currY + i * (-lineDirection[0]);

//        if(tmp.x < 0 || tmp.x >= inputMatrix.cols || tmp.y < 0 || tmp.y >= inputMatrix.rows)
//            continue;

//        if(((int)(inputMatrix.at<uchar>(tmp.y,tmp.x))) > 0)
//            return true;

//        tmp.x =   currX + i * (-lineDirection[1]);
//        tmp.y =   currY + i * lineDirection[0];

//        if(tmp.x < 0 || tmp.x >= inputMatrix.cols || tmp.y < 0 || tmp.y >= inputMatrix.rows)
//            continue;

//        if(((int)(inputMatrix.at<uchar>(tmp.y,tmp.x))) > 0)
//            return true;

        if( lineOrientation == ABS_X_GREATER_Y  || lineOrientation == ABS_X_EQUAL_Y)
        {
            if(currX < 0 || currX >= inputMatrix.cols || (currY + (1*i)) < 0 || (currY + (1*i)) >= inputMatrix.rows)
               continue;
            if ( inputMatrix.at<uchar>((currY + (1*i)), currX ) > 0 )
                return true;

            if(currX < 0 || currX >= inputMatrix.cols || (currY - (1*i)) < 0 || (currY - (1*i)) >= inputMatrix.rows)
               continue;
            if ( inputMatrix.at<uchar>((currY - (1*i)), currX) > 0 )
                return true;
        }
       if ( lineOrientation == ABS_X_LOWER_Y  || lineOrientation == ABS_X_EQUAL_Y)
        {
            if((currX + (1*i)) < 0 || (currX + (1*i)) >= inputMatrix.cols || currY < 0 || currY >= inputMatrix.rows)
                continue;
            if ( inputMatrix.at<uchar>(currY, (currX + (1*i)) ) > 0 )
                return true;

            if((currX - (1*i)) < 0 || (currX - (1*i)) >= inputMatrix.cols || currY < 0 || currY >= inputMatrix.rows)
                continue;
            if ( inputMatrix.at<uchar>(currY, (currX - (1*i))) > 0 )
                return true;
        }
       if( lineOrientation == ABS_X_EQUAL_Y)
        {
           if(lineDirection[0] == lineDirection[1])
           {
               if( (currX + (1*i)) < 0 ||  (currX + (1*i)) >= inputMatrix.cols || (currY + (1*i)) < 0 || (currY + (1*i)) >= inputMatrix.rows)
                   continue;
                if ( inputMatrix.at<uchar>( (currY + (1*i)), (currX + (1*i))) > 0 )
                    return true;

                if( (currX - (1*i)) < 0 ||  (currX - (1*i)) >= inputMatrix.cols || (currY - (1*i)) < 0 || (currY - (1*i)) >= inputMatrix.rows)
                    continue;
                if ( inputMatrix.at<uchar>( (currY - (1*i)), (currX - (1*i))) > 0 )
                    return true;
           }
           else
           {
               if( (currX + (1*i)) < 0 ||  (currX + (1*i)) >= inputMatrix.cols || (currY - (1*i)) < 0 || (currY - (1*i)) >= inputMatrix.rows)
                   continue;
               if ( inputMatrix.at<uchar>(  (currY - (1*i)), (currX + (1*i))) > 0 )
                   return true;

               if( (currX - (1*i)) < 0 ||  (currX - (1*i)) >= inputMatrix.cols || (currY + (1*i)) < 0 || (currY + (1*i)) >= inputMatrix.rows)
                   continue;
               if ( inputMatrix.at<uchar>( (currY + (1*i)),  (currX - (1*i))) > 0 )
                   return true;
           }
        }

    }

    return false;
}

u_int16_t Hough::calculateMinimalVotes(u_int16_t inputCannyEdgePixelDensity, u_int16_t inputEdgePixelCounter)
{
    int lowDensityValue = 12000;

    if(inputCannyEdgePixelDensity <= 15 && inputEdgePixelCounter > lowDensityValue){
        return 220;
    }
    else if(inputCannyEdgePixelDensity <= 32 && inputEdgePixelCounter > lowDensityValue){
        return 140;
    }
    else if(inputCannyEdgePixelDensity <= 70 && inputEdgePixelCounter > lowDensityValue){
        return 130;
    }
    else if(inputCannyEdgePixelDensity <= 100 && inputEdgePixelCounter > lowDensityValue){
        return 100;
    }

    return 40;
}

u_int32_t Hough::calculateGreatestCommonDivisor(u_int32_t a, u_int32_t b)
{
    if(a == 0 || b == 0)
        return 1;

    while(true)
    {
        if(a==0)
            return b;

        b%=a;

        if(b==0)
            return a;

        a%=b;
    }
    return 0;
}

void Hough::compareHoughLinesWithCannyEdges(std::vector<Line>& outputLines, std::vector<cv::Vec2f>& inputLines, cv::Mat& inputCannyImage)
{
    // ***********************************
    // check lines with Canny-edge picture
    // ***********************************
    // iterate through line vector received from Hough-Transform
    int numberOfLinePixelsFound = 0;
    int currentGapSize = 0;

    for(uint i = 0; i < inputLines.size(); i++){

        float rho = inputLines[i][0],
                theta = inputLines[i][1];

        Point2d currentPoint;

        double a = cos(theta),
                b = sin(theta);

        double x0 = a*rho,
                y0 = b*rho;

        lineDirection[0] = cvRound(x0 + (-imageDiagonal)*(-b)) - cvRound(x0 + imageDiagonal*(-b));
        lineDirection[1] = cvRound(y0 + (-imageDiagonal)*(a)) - cvRound(y0 + imageDiagonal*(a));

        if( abs(lineDirection[0]) > abs(lineDirection[1]) )
            lineOrientation = ABS_X_GREATER_Y;
        else if ( abs(lineDirection[0]) < abs(lineDirection[1]) )
            lineOrientation = ABS_X_LOWER_Y;
        else
            lineOrientation = ABS_X_EQUAL_Y;

        //int gcd = calculateGreatestCommonDivisor( fabs(lineDirection[0]) , fabs(lineDirection[1]) );

        //lineDirection[0] = lineDirection[0] / gcd;
        //lineDirection[1] = lineDirection[1] / gcd;

        Point2d startPoint,
        endPoint;


        // default values for checks
        startPoint.x = -1;
        numberOfLinePixelsFound = 0;

        bool gapped = false;

        // iterate from start to end of a line and check where the Canny-edge starts and ends
        for(int currentLinePixel = imageDiagonal; currentLinePixel > -imageDiagonal; currentLinePixel-=2){

            currentPoint.x = cvRound(x0 + currentLinePixel*(-b));
            currentPoint.y = cvRound(y0 + currentLinePixel*(a));

                if(checkEnvironmentInRightAngle(inputCannyImage, currentPoint.x, currentPoint.y)){

                    // if default value -> set startPoint
                    if(startPoint.x == -1){
                        startPoint = currentPoint;
                    }
                    numberOfLinePixelsFound ++;
                    gapped = false;

                }else{

                    // continue if no startPoint was defined
                    if(startPoint.x == -1){
                        continue;
                    }

                    // check gap between two lines
                    // if gap is smaller than maximal gap size then continue
                    // else reset is line is not long enough
                    currentGapSize ++;
                    if(currentGapSize < maximalLineGap){

                        if(!gapped){
                            endPoint = currentPoint;
                            gapped = true;
                        }
                        continue;
                    }else if(numberOfLinePixelsFound < minimumLineSize){

                        numberOfLinePixelsFound = 0;
                        currentGapSize = 0;
                        startPoint.x = -1;
                        gapped = false;
                        continue;
                    }

                    outputLines.push_back(Line(startPoint, endPoint));

                    numberOfLinePixelsFound = 0;
                    currentGapSize = 0;
                    gapped = false;
                    startPoint.x = -1;
                }
        }
    }
}

void Hough::getCannyImage(cv::Mat& outputCannyImage, cv::Mat& inputGrayLevelImage)
{
    double cannyEdgePixelDensity;
    double edgePixelCounter=0;
    int lowThreshValue = 60;
    // pre preperation for auto parameter adjusting
    // if canny images is very dense then blur the picture and repeat canny
    do{
        Canny(inputGrayLevelImage, outputCannyImage, lowThreshValue, lowThreshValue*3);

        for(int i = 0; i < inputGrayLevelImage.rows; i++){
            for(int j = 0; j < inputGrayLevelImage.cols; j++){

                if((int)outputCannyImage.at<uchar>(i,j) > 0){
                    ++edgePixelCounter;
                }
            }
        }

        cannyEdgePixelDensity = (inputGrayLevelImage.rows * inputGrayLevelImage.cols) / edgePixelCounter;

        if(cannyEdgePixelDensity <= 15){
            blur(inputGrayLevelImage,inputGrayLevelImage, Size(5,5), Point(-1,-1));
            lowThreshValue += 20;
            edgePixelCounter = 0;
        }
    }while(cannyEdgePixelDensity <= 15);

    // set minvotes according to canny pixel density
    minimalHoughVotes = calculateMinimalVotes(cannyEdgePixelDensity, edgePixelCounter);
}

} // namespace formseher
