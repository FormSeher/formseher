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
    return &edl;
}

void EDLConfigDialog::on_sobelKernelSize_valueChanged(int sobelKernelSize)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelScale_valueChanged(double sobelScale)
{
    emit configChanged();
}

void EDLConfigDialog::on_sobelDelta_valueChanged(double sobelDelta)
{
    emit configChanged();
}

void EDLConfigDialog::on_gaussianKernelSize_valueChanged(int gaussianKernelSize)
{
    emit configChanged();
}

void EDLConfigDialog::on_anchorThreshold_valueChanged(int anchorThreshold)
{
    emit configChanged();
}

void EDLConfigDialog::on_angleTolerance_valueChanged(double angleTolerance)
{
    emit configChanged();
}
