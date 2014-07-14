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

#include "gui/linedetection/edl2/edl2configdialog.h"
#include "ui_edl2configdialog.h"
#include "mathutil.h"

namespace formseher
{

EDL2ConfigDialog::EDL2ConfigDialog(QWidget *parent) :
    LineDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::EDL2ConfigDialog)
{
    ui->setupUi(this);
}

EDL2ConfigDialog::~EDL2ConfigDialog()
{
    delete ui;
}

LineDetectionAlgorithm* EDL2ConfigDialog::createAlgorithm()
{
    return new EDL2(
        ui->gaussianKernelSize->value(),
        ui->minAnchorThreshold->value(),
        ui->anchorStepping->value(),
        ui->anchorThreshold->value(),
        ui->angleTolerance->value() * math::m_pi / 180.0,
        ui->minLineLength->value()
    );
}

void EDL2ConfigDialog::on_minAnchorThreshold_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_anchorStepping_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_gaussianKernelSize_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_anchorThreshold_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_angleTolerance_valueChanged(double)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_minLineLength_valueChanged(int)
{
    emit configChanged();
}

} // namespace formseher
