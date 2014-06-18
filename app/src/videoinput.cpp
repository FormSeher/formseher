#include "videoinput.h"

namespace formseher
{

VideoInput::VideoInput()
    : cv::VideoCapture()
{
}

VideoInput::VideoInput(const std::string &string)
    : cv::VideoCapture(string)
{
}

VideoInput::VideoInput(int device)
    : cv::VideoCapture(device)
{
}

VideoInput &VideoInput::operator>>(cv::Mat &image)
{
    cv::VideoCapture::operator>>(this->image);
    image = this->image;

    return *this;
}

cv::Mat VideoInput::getLastImage()
{
    return image;
}

} // namespace formseher
