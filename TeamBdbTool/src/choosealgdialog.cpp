#include "choosealgdialog.h"
#include "ui_choosealgdialog.h"

ChooseALGDialog::ChooseALGDialog(formseher::LineDetectionAlgorithm *lineDeteciontAlgorithm, QWidget *parent) :
    lineDeteciontAlgorithm(lineDeteciontAlgorithm),
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
    lineDeteciontAlgorithm = new formseher::EDL();
}

void ChooseALGDialog::on_radioButton_3_clicked()
{
    lineDeteciontAlgorithm = new formseher::EDL2();
}

void ChooseALGDialog::on_radioButton_2_clicked()
{
    lineDeteciontAlgorithm = new formseher::Hough();
}
