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

#include "gui/objectdetection/teamb/objectdetectionalgorithmteambdialog.h"
#include "ui_objectdetectionalgorithmteambdialog.h"
#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"

namespace formseher
{
ObjectDetectionAlgorithmTeamBDialog::ObjectDetectionAlgorithmTeamBDialog(QWidget *parent) :
    ObjectDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::ObjectDetectionAlgorithmTeamBDialog)
{
    ui->setupUi(this);
}

ObjectDetectionAlgorithmTeamBDialog::~ObjectDetectionAlgorithmTeamBDialog()
{
    delete ui;
}

ObjectDetectionAlgorithm *ObjectDetectionAlgorithmTeamBDialog::createAlgorithm()
{
    return new ObjectDetectionAlgorithmTeamB(ui->minRating->value(),
                                             ui->maxAngleThreshold->value(),
                                             ui->maxDistanceThreshold->value(),
                                             ui->midPointEnvironment->value(),
                                             ui->fastMode->isChecked());
}

void ObjectDetectionAlgorithmTeamBDialog::on_minRating_valueChanged(int){
    emit configChanged();
}

void ObjectDetectionAlgorithmTeamBDialog::on_maxAngleThreshold_valueChanged(double){
    emit configChanged();
}

void ObjectDetectionAlgorithmTeamBDialog::on_maxDistanceThreshold_valueChanged(double){
    emit configChanged();
}

void ObjectDetectionAlgorithmTeamBDialog::on_midPointEnvironment_valueChanged(int){
    emit configChanged();
}

void ObjectDetectionAlgorithmTeamBDialog::on_fastMode_toggled(bool){
    emit configChanged();
}
}
