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

#include "gui/linedetection/hough/houghconfigdialog.h"
#include "ui_houghconfigdialog.h"

namespace formseher
{

HoughConfigDialog::HoughConfigDialog(QWidget *parent) :
    LineDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::HoughConfigDialog)
{
    ui->setupUi(this);
}

HoughConfigDialog::~HoughConfigDialog()
{
    delete ui;
}

LineDetectionAlgorithm* HoughConfigDialog::createAlgorithm()
{
    return new Hough(
                ui->checkEnvironmentSize->value(),
                ui->maximalLineGap->value(),
                ui->minimumLineSize->value()
    );
}

void HoughConfigDialog::on_checkEnvironmentSize_valueChanged(int)
{
    emit configChanged();
}

void HoughConfigDialog::on_maximalLineGap_valueChanged(int)
{
    emit configChanged();
}

void HoughConfigDialog::on_minimumLineSize_valueChanged(int)
{
    emit configChanged();
}

} // namespace formseher
