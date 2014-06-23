#include "committodbdialog.h"
#include "ui_committodbdialog.h"

commitToDBDialog::commitToDBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commitToDBDialog)
{
    ui->setupUi(this);
}

commitToDBDialog::~commitToDBDialog()
{
    delete ui;
}
