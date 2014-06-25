#include "include/saveobjectdialog.h"
#include "ui_saveobjectdialog.h"

SaveObjectDialog::SaveObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveObjectDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Save object");
}

SaveObjectDialog::~SaveObjectDialog()
{
    delete ui;
}

QString SaveObjectDialog::getObjectName() const
{
    return ui->lineEditObjectName->text();
}
