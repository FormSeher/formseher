/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

#ifndef FS_VIDEOINPUT_H
#define FS_VIDEOINPUT_H

#include <opencv2/highgui/highgui.hpp>

namespace formseher
{

class VideoInput : public cv::VideoCapture
{
public:
    /**
     * @brief VideoInput
     * @see cv::VideoCapture::VideoCapture()
     */
    VideoInput();

    /**
     * @brief Create VideoInput for a video file.
     * @param string Path to the video file.
     * @see cv::VideoCapture::VideoCapture(const string&)
     */
    VideoInput(const std::string& string);

    /**
     * @brief Create VideoInput for a device (e.g. webcam)
     * @param device Id of the device.
     * @see cv::VideoCapture::VideoCapture(int)
     */
    VideoInput(int device);

    /**
     * @brief Reads the next image from the video stream.
     * @return The new image.
     */
    VideoInput& operator>>(cv::Mat& image);

    /**
     * @brief Returns the last image retrieved by readNextImage().
     * @return Returns the latest image.
     */
    cv::Mat getLastImage();

private:
    /**
     * @brief The image read by readNextImage().
     */
    cv::Mat image;
};

}

#endif // FS_VIDEOINPUT_H
