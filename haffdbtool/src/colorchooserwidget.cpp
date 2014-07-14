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

// Database tool
#include "colorchooserwidget.h"
#include "ui_colorchooserwidget.h"

// Qt
#include <QColor>
#include <QColorDialog>

ColorChooserWidget::ColorChooserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorChooserWidget)
{
    ui->setupUi(this);

    this->colors.first = Qt::magenta;
    this->colors.second = Qt::green;

    ui->buttonPossibleColor->setText(this->colors.first.name());
    ui->buttonPossibleColor->setPalette(QPalette(this->colors.first));
    ui->buttonPossibleColor->setAutoFillBackground(true);
    ui->buttonChosenColor->setText(this->colors.second.name());
    ui->buttonChosenColor->setPalette(QPalette(this->colors.second));
    ui->buttonChosenColor->setAutoFillBackground(true);

    connect(ui->buttonPossibleColor, SIGNAL(clicked()), this, SLOT(changePossibleColor()));
    connect(ui->buttonChosenColor, SIGNAL(clicked()), this, SLOT(changeChosenColor()));
}

ColorChooserWidget::~ColorChooserWidget()
{
    delete ui;
}

void ColorChooserWidget::changePossibleColor()
{
    QColor color = QColorDialog::getColor(this->colors.first, this);
    if (color.isValid())
    {
        this->colors.first = color;
        ui->buttonPossibleColor->setText(this->colors.first.name());
        ui->buttonPossibleColor->setPalette(QPalette(this->colors.first));
        ui->buttonPossibleColor->setAutoFillBackground(true);
    }
}

void ColorChooserWidget::changeChosenColor()
{
    QColor color = QColorDialog::getColor(this->colors.second, this);
    if (color.isValid())
    {
        this->colors.second = color;
        ui->buttonChosenColor->setText(this->colors.second.name());
        ui->buttonChosenColor->setPalette(QPalette(this->colors.second));
        ui->buttonChosenColor->setAutoFillBackground(true);
    }
}

std::pair<QColor, QColor> ColorChooserWidget::getColors() const
{
    return this->colors;
}

void ColorChooserWidget::setColors(std::pair<QColor, QColor> colors)
{
    this->colors = colors;
}
