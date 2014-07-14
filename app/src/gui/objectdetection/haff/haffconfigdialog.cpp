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

#include "gui/objectdetection/haff/haffconfigdialog.h"
#include "ui_haffconfigdialog.h"

#include "objectdetection/haff/haff.h"

namespace formseher
{

HaffConfigDialog::HaffConfigDialog(QWidget *parent) :
    ObjectDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::HaffConfigDialog)
{
    ui->setupUi(this);
}

HaffConfigDialog::~HaffConfigDialog()
{
    delete ui;
}

ObjectDetectionAlgorithm* HaffConfigDialog::createAlgorithm()
{
    return new Haff(ui->numberOfBestHypotheses->value(),
                    ui->numberOfDetectedObjects->value(),
                    ui->minimalObjectRating->value(),
                    ui->coverWeight->value(),
                    ui->angleWeight->value(),
                    ui->positionWeight->value()
    );
}

void HaffConfigDialog::on_numberOfBestHypotheses_valueChanged(int)
{
    emit configChanged();
}

void HaffConfigDialog::on_numberOfDetectedObjects_valueChanged(int)
{
    emit configChanged();
}

void HaffConfigDialog::on_minimalObjectRating_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_coverWeight_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_angleWeight_valueChanged(double)
{
    emit configChanged();
}

void HaffConfigDialog::on_positionWeight_valueChanged(double)
{
    emit configChanged();
}

} // namespace formseher

