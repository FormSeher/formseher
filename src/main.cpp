/*
 * main.cpp
 *
 * Created on: 21.03.2014
 * Author: scar, Simon Kerler
 */

extern "C"
{
#include "lsd/lsd.h"
}

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	// Check if an image path was provided via cli parameter
	if(argc != 2)
	{
		std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	// Load the image and check if it was loaded successfully
	cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		std::cout <<  "Could not open or find the image" << std::endl;
		return -1;
	}

	// Convert the image to grayscale
	cv::Mat imageGray;
	cv::cvtColor(image, imageGray, CV_RGB2GRAY);

	// Convert the image's pixel values to a double-array (I think there's a more efficient way ;))
	int rows = image.rows;
	int columns = image.cols;

	double imageDouble[image.cols * image.rows];

	for(int row = 0; row < rows; ++row)
	{
		unsigned char* rowPointer = imageGray.ptr(row);
		for(int column = 0; column < columns; ++column)
		{
			imageDouble[column + row * columns] = (double) (*rowPointer++);
		}
	}

	// Call LSD
	int segmentCount = 0;
	double* lineSegments = lsd(&segmentCount, imageDouble, columns, rows);

	// Draw the result to the color image
	for(int i = 0; i < segmentCount; ++i)
	{
		double* line = lineSegments + 7 * i;
		cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(255, 0, 255));
	}

	// Display image and wait for termination
	cv::namedWindow("Display window");
	cv::imshow("Display window", image);

	cv::waitKey(0);
	return 0;
}
