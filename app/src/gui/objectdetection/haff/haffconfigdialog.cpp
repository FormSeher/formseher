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
    return new Haff();
}

} // namespace formseher
