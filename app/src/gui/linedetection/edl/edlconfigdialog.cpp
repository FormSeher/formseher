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

#include "gui/linedetection/edl/edlconfigdialog.h"
#include "ui_edlconfigdialog.h"
#include "mathutil.h"

namespace formseher
{

EDLConfigDialog::EDLConfigDialog(QWidget *parent) :
    LineDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::EDLConfigDialog)
{
    ui->setupUi(this);
}

EDLConfigDialog::~EDLConfigDialog()
{
    delete ui;
}

LineDetectionAlgorithm* EDLConfigDialog::createAlgorithm()
{
    return new EDL(
                ui->sobelKernelSize->value(),
                ui->sobelScale->value(),
                ui->sobelDelta->value(),
                ui->gaussianKernelSize->value(),
                ui->anchorThreshold->value(),
                ui->angleTolerance->value() * math::m_pi / 180.0,
                ui->minLineLength->value()
    );
}

void EDLConfigDialog::on_sobelKernelSize_valueChanged(int)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelScale_valueChanged(double)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelDelta_valueChanged(double)
{
    emit configChanged();
}

void EDLConfigDialog::on_gaussianKernelSize_valueChanged(int)
{
    emit configChanged();
}

void EDLConfigDialog::on_anchorThreshold_valueChanged(int)
{
    emit configChanged();
}

void EDLConfigDialog::on_angleTolerance_valueChanged(double)
{
    emit configChanged();
}

void EDLConfigDialog::on_minLineLength_valueChanged(int)
{
    emit configChanged();
}

} // namespace formseher
