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
