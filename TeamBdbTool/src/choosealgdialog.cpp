#include "choosealgdialog.h"
#include "ui_choosealgdialog.h"

ChooseALGDialog::ChooseALGDialog(formseher::LineDetectionAlgorithm *lineDeteciontAlgorithm, QWidget *parent) :
    lineDetecionAlgorithm(lineDeteciontAlgorithm),
    QDialog(parent),
    ui(new Ui::ChooseALGDialog)
{
    ui->setupUi(this);

}

ChooseALGDialog::~ChooseALGDialog()
{
    delete ui;
}

void ChooseALGDialog::on_radioButton_clicked()
{
    lineDetecionAlgorithm = new formseher::EDL();
}

void ChooseALGDialog::on_radioButton_3_clicked()
{
    lineDetecionAlgorithm = new formseher::EDL2();
}

void ChooseALGDialog::on_radioButton_2_clicked()
{
    lineDetecionAlgorithm = new formseher::Hough();
}
