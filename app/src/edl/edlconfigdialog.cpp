#include "edl/edlconfigdialog.h"
#include "ui_edlconfigdialog.h"

EDLConfigDialog::EDLConfigDialog(QWidget *parent) :
    AlgorithmConfigDialog(parent),
    ui(new Ui::EDLConfigDialog)
{
    ui->setupUi(this);
}

EDLConfigDialog::~EDLConfigDialog()
{
    delete ui;
}

Algorithm* EDLConfigDialog::getAlgorithm()
{
    return 0;
}
