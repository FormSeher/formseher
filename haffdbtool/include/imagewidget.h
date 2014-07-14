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

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

// Database tool
#include "imagemode.h"

// Formseher project
#include "line.h"

// Qt
#include <QWidget>

namespace Ui {
class ImageWidget;
}

/**
 * @brief The ImageWidget class is a Qt UI class which displays the image,
 * modebuttons and two lists of lines (possible and chosen lines).
 */
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ImageWidget standard constructor.
     * @param parent Parent widget.
     */
    explicit ImageWidget(QWidget *parent = 0);

    /**
     * @brief ImageWidget destructor.
     */
    ~ImageWidget();

public slots:
    /**
     * @brief slot_configurationChanged Slot that gets connected to a configuration change.
     */
    void slot_configurationChanged();

    /**
     * @brief slot_repaint Slot that gets connected to a signal if a new image to be displayed gets calculated.
     * @param image Image to be displayed.
     */
    void slot_repaint(cv::Mat image);

    /**
     * @brief slot_setLines Slot that gets connected to a change in the line vectors of the LearningObject.
     * @param lines Lines to be set to the two listViews.
     */
    void slot_setLines(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line> > lines);

    /**
     * @brief slot_doubleClicked Slot that gets connected to the doubleclick signal of the two listViews.
     */
    void slot_doubleClicked();

signals:
    /**
     * @brief signal_configurationChanged Signal that gets emmited if the display configuration changed.
     */
    void signal_configurationChanged(ImageMode, int, int);

    /**
     * @brief signal_lineDoubleClicked Signal that gets emmited if a line of the two lists gets doubleclicked.
     */
    void signal_lineDoubleClicked(std::pair<int, int>);


private:
    Ui::ImageWidget *ui;
};

#endif // IMAGEWIDGET_H
