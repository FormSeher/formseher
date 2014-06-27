#include "include/drawinfodialog.h"
#include "ui_drawinfodialog.h"

bool DrawInfoDialog::showEverytime = true;

DrawInfoDialog::DrawInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawInfoDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Drawing Note");

    ui->checkBoxShow->setChecked(DrawInfoDialog::showEverytime);

    // Slot connection
    connect(ui->checkBoxShow, SIGNAL(toggled(bool)), this, SLOT(slot_toggleShow(bool)));
}

DrawInfoDialog::~DrawInfoDialog()
{
    delete ui;
}

void DrawInfoDialog::slot_toggleShow(bool value)
{
    showEverytime = value;
}

int DrawInfoDialog::exec()
{
    if( ! DrawInfoDialog::showEverytime )
        return QDialog::Accepted;
    else
        return QDialog::exec();
}
