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
                                             ui->maxDistanceThreshold->value());
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
}
