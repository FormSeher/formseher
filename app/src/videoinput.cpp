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
