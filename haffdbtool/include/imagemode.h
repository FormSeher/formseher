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

#ifndef IMAGEMODE_H
#define IMAGEMODE_H

/**
 * @brief The ImageMode enum holds values for the currently chosen image display mode.
 */
enum ImageMode
{
    MODE_IMG,           // Display the original image.
    MODE_GREY,          // Display the image as grayscale.
    MODE_LINES,         // Display just the chosen lines on a neutral background.
    MODE_GREY_LINES,    // Display the image as grayscale with the chosen lines as overlay.
    MODE_IMG_LINES      // Display the original image with the chosen lines as overlay.
};


#endif // IMAGEMODE_H
