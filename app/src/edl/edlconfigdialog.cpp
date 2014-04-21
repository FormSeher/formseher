#include "edl/edlconfigdialog.h"
#include "ui_edlconfigdialog.h"

EDLConfigDialog::EDLConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EDLConfigDialog)
{
    ui->setupUi(this);
}

EDLConfigDialog::~EDLConfigDialog()
{
    delete ui;
}
