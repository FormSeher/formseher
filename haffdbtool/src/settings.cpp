#include "include/settings.h"
#include "ui_settings.h"

#include "linedetection/linedetectionalgorithm.h"
#include "linedetection/hough/hough.h"
#include "linedetection/edl/edl.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->comboBoxAlgorithm->addItem("Hough");
    ui->comboBoxAlgorithm->addItem("EDL");

    this->setWindowTitle("Settings");

    slot_settingsChanged();

    // Slot connection
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slot_settingsChanged()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::slot_settingsChanged()
{
    formseher::LineDetectionAlgorithm* algorithm;

    if(ui->comboBoxAlgorithm->currentText() == "Hough")
    {
        algorithm = new formseher::Hough();
    }
    else if(ui->comboBoxAlgorithm->currentText() == "EDL")
    {
        algorithm = new formseher::EDL();
    }

    emit signal_newSettings(algorithm, ui->widgetColorChooser->getColors(), ui->spinBoxThickness->value());
}
