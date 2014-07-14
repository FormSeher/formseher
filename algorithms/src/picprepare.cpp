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

#include "picprepare.h"

namespace formseher
{

/**
 * @brief PicturePrepare::PicturePrepare
 * @param src
 */
PicturePrepare::PicturePrepare(Mat src)
{
    m_srcPic = src;
}

/**
 * @brief PicturePrepare::startPreparePicture
 * @return allready prepared picture
 */
Mat PicturePrepare::startPreparePicture()
{
    Mat src_gray;
    Mat grad;

    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    //different blur effects, test for the best speed

    // the gaussian blur
   GaussianBlur( m_srcPic, m_srcPic, Size(3,3), 0, 0, BORDER_DEFAULT );
    //box filter
    //blur( src, src, Size(5,5),Point(-1,-1));
    //median blur
   // medianBlur ( src, src, 3 );

    // Convert it to gray
    cvtColor( m_srcPic, src_gray, COLOR_RGB2GRAY );

    // Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    // Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    // Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    //Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );


    return grad;
}

}

