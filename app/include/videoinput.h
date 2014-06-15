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
