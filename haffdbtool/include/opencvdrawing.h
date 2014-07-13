#ifndef OPENCVDRAWING_H
#define OPENCVDRAWING_H

// Formseher project
#include "line.h"

/**
 * @brief The OpencvDrawing class which holds functions to display a image and draw lines within.
 */
class OpencvDrawing
{
public:
    /**
     * @brief OpencvDrawing empty constructor.
     */
    OpencvDrawing();

    /**
     * @brief drawLines Static function which opens a cv::imshow() with the current image, to draw in.
     * @param image Image that gets shown.
     * @return Vector of Lines that were drawn on the image.
     */
    static std::vector<formseher::Line> drawLines(cv::Mat image);

private:
    /** @brief startPoint Startpoint of the drawed line.*/
    static cv::Point2i startPoint;

    /** @brief lineVector Vector that holds all drawed lines.*/
    static std::vector<formseher::Line> lineVector;

    /** @brief resultImage Image that gets manipulated to display drawing. */
    static cv::Mat resultImage;

    /**
     * @brief CallBackFunc Mouse callback function for the cv::imshow(). Gets calles everytime a mouse event occures.
     * @param event Enum value that indicates which mouse event occured.
     * @param x X coordinate of the mouse event.
     * @param y Y coordinate of the mouse event.
     * @param flags Enum value that indicates which additional flags are presenst (e.g. CTRL, ALT).
     * @param image Additional pointer to the original image.
     */
    static void CallBackFunc(int event, int x, int y, int flags, void* image);
};

#endif // OPENCVDRAWING_H
