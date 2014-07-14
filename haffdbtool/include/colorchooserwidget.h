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

#ifndef COLORCHOOSERWIDGET_H
#define COLORCHOOSERWIDGET_H

// Qt
#include <QWidget>

namespace Ui {
class colorChooserWidget;
}

/**
 * @brief The ColorChooserWidget class is a Qt UI class wich represents
 * a widget with two color chooser buttons.
 */
class ColorChooserWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ColorChooserWidget standard constructor.
     * @param parent Parent widget.
     */
    explicit ColorChooserWidget(QWidget *parent = 0);

    /**
     * @brief ColorChooserWidget destructor.
     */
    ~ColorChooserWidget();

    /**
     * @brief setColors Setter for the two color button's color.
     * @param colors Colors to be set.
     */
    void setColors(std::pair<QColor, QColor> colors);

    /**
     * @brief getColors Getter for the two selected colors.
     * @return Pair of the two selected colors.
     */
    std::pair<QColor, QColor> getColors() const;

private slots:
    /**
     * @brief changePossibleColor Slot that gets connected to the possible color button.
     */
    void changePossibleColor();

    /**
     * @brief changeChosenColor Slot that gets connected to the chosen color button.
     */
    void changeChosenColor();

private:
    Ui::colorChooserWidget *ui;

    /**
     * @brief colors Pair that holds the two color values.
     */
    std::pair<QColor, QColor> colors;
};

#endif // COLORCHOOSERWIDGET_H
