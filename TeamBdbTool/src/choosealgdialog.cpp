#include "choosealgdialog.h"
#include "ui_choosealgdialog.h"
#include <mathutil.h>

ChooseALGDialog::ChooseALGDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseALGDialog)
{
    ui->setupUi(this);

}

ChooseALGDialog::~ChooseALGDialog()
{
    delete ui;
}


void ChooseALGDialog::on_buttonBox_accepted()
{
    QString str = ui->choosealgdialog->tabText(ui->choosealgdialog->currentIndex());
    if (str == "EDL")
    {
        alg = new formseher::EDL(ui->EDL_SobelKernelSize->value(),
                                 ui->EDL_SobelScale->value(),
                                 ui->EDL_SobelDelta->value(),
                                 ui->EDL_GaussKernelSize->value(),
                                 ui->EDL_AnchorThreshold->value(),
                                 ui->EDL_AngleTolerance->value() * formseher::math::m_pi / 180.0,
                                 ui->EDL_MinLineLength->value()
                                 );
    }
    if (str == "EDL2")
    {
        alg = new formseher::EDL2(ui->EDL2_GaussKernalSize->value(),
                                  ui->EDL2_MinAnchorThreshold->value(),
                                  ui->EDL2_AnchorStepping->value(),
                                  ui->EDL2_AnchorThreshold->value(),
                                  ui->EDL2_AngleTolerance->value() * formseher::math::m_pi / 180.0,
                                  ui->EDL2_MinLineLength->value()
                                  );
    }
    if (str == "Hough")
    {
        alg = new formseher::Hough(ui->Hough_CheckEnvironmentSize->value(),
                                                      ui->Hough_MaxLineGap->value(),
                                                      ui->Hough_minLineLength->value()
                                                      );
    }
}
