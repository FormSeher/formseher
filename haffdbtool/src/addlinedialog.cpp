// Database tool
#include "include/addlinedialog.h"
#include "ui_addlinedialog.h"

// Formseher project
#include "line.h"

AddLineDialog::AddLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Line");
}

AddLineDialog::~AddLineDialog()
{
    delete ui;
}

formseher::Line AddLineDialog::getLine()
{
    return formseher::Line(ui->spinBoxStartX->value(), ui->spinBoxStartY->value(),
                           ui->spinBoxEndX->value(), ui->spinBoxEndY->value());
}
