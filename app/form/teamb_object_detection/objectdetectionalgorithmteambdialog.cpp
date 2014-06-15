#include "objectdetectionalgorithmteambdialog.h"
#include "ui_objectdetectionalgorithmteambdialog.h"

ObjectDetectionAlgorithmTeamBDialog::ObjectDetectionAlgorithmTeamBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectDetectionAlgorithmTeamBDialog)
{
    ui->setupUi(this);
}

ObjectDetectionAlgorithmTeamBDialog::~ObjectDetectionAlgorithmTeamBDialog()
{
    delete ui;
}
