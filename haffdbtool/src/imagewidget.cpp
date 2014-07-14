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
#include "include/imagewidget.h"
#include "ui_imagewidget.h"

// Formseher project
#include "line.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);

    // Slot connection
    connect(ui->radioImageOriginal, SIGNAL(clicked()), this, SLOT(slot_configurationChanged()));
    connect(ui->radioImageGreyscale, SIGNAL(clicked()), this, SLOT(slot_configurationChanged()));
    connect(ui->radioImageNone, SIGNAL(clicked()), this, SLOT(slot_configurationChanged()));
    connect(ui->checkBoxLines, SIGNAL(clicked()), this, SLOT(slot_configurationChanged()));

    connect(ui->listWidgetPossibleLines, SIGNAL(currentRowChanged(int)), ui->listWidgetChosenLines, SLOT(clearSelection()));
    connect(ui->listWidgetChosenLines, SIGNAL(currentRowChanged(int)), ui->listWidgetPossibleLines, SLOT(clearSelection()));
    connect(ui->listWidgetPossibleLines, SIGNAL(currentRowChanged(int)), this, SLOT(slot_configurationChanged()));
    connect(ui->listWidgetChosenLines, SIGNAL(currentRowChanged(int)), this, SLOT(slot_configurationChanged()));

    connect(ui->listWidgetPossibleLines, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_doubleClicked()));
    connect(ui->listWidgetChosenLines, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_doubleClicked()));
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::slot_configurationChanged()
{
    ImageMode mode = ImageMode::MODE_IMG;

    if(ui->radioImageOriginal->isChecked())
    {
        ui->checkBoxLines->setEnabled(true);
        if(ui->checkBoxLines->isChecked())
        {
            mode = ImageMode::MODE_IMG_LINES;
        }
        else
        {
            mode = ImageMode::MODE_IMG;
        }
    }
    else if(ui->radioImageGreyscale->isChecked())
    {
        ui->checkBoxLines->setEnabled(true);
        if(ui->checkBoxLines->isChecked())
        {
            mode = ImageMode::MODE_GREY_LINES;
        }
        else
        {
            mode = ImageMode::MODE_GREY;
        }
    }
    else if(ui->radioImageNone->isChecked())
    {
        ui->checkBoxLines->setEnabled(false);
        mode = ImageMode::MODE_LINES;
    }

    emit signal_configurationChanged(mode,
                                     ui->listWidgetPossibleLines->currentRow(),
                                     ui->listWidgetChosenLines->currentRow());
}

void ImageWidget::slot_repaint(cv::Mat image)
{
    QImage qImage = QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->lableImage->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->lableImage->setPixmap(QPixmap::fromImage(scaledImage));
}

void ImageWidget::slot_setLines(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>> lines)
{
    ui->listWidgetPossibleLines->clear();
    ui->listWidgetChosenLines->clear();

    for(formseher::Line possibleLine : lines.first)
    {
        std::stringstream listtext;
        listtext << std::endl << "Line " << possibleLine.getStart() << " → " << possibleLine.getEnd() << std::endl;
        ui->listWidgetPossibleLines->addItem(new QListWidgetItem(tr(listtext.str().c_str())));
    }
    for(formseher::Line chosenLine : lines.second)
    {
        std::stringstream listtext;
        listtext << std::endl << "Line " << chosenLine.getStart() << " → " << chosenLine.getEnd() << std::endl;
        ui->listWidgetChosenLines->addItem(new QListWidgetItem(tr(listtext.str().c_str())));
    }
}


void ImageWidget::slot_doubleClicked()
{
    emit signal_lineDoubleClicked(std::pair<int, int>(
                                      ui->listWidgetPossibleLines->currentRow(),
                                      ui->listWidgetChosenLines->currentRow()));
}
