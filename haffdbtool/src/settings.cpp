// Database tool
#include "include/settings.h"
#include "ui_settings.h"

// Formseher project
#include "linedetection/edl/edl.h"
#include "linedetection/edl2/edl2.h"
#include "linedetection/hough/hough.h"
#include "linedetection/linedetectionalgorithm.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->comboBoxAlgorithm->addItem("Hough");
    ui->comboBoxAlgorithm->addItem("EDL");
    ui->comboBoxAlgorithm->addItem("EDL2");

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
    else if(ui->comboBoxAlgorithm->currentText() == "EDL2")
    {
        algorithm = new formseher::EDL2();
    }

    emit signal_newSettings(algorithm, ui->widgetColorChooser->getColors(), ui->spinBoxThickness->value());
}
