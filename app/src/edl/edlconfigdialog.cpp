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
    edl.setSobelKernelSize(sobelKernelSize);
}

void EDLConfigDialog::on_sobelScale_valueChanged(double sobelScale)
{
    edl.setSobelScale(sobelScale);
}

void EDLConfigDialog::on_sobelDelta_valueChanged(double sobelDelta)
{
    edl.setSobelDelta(sobelDelta);
}

void EDLConfigDialog::on_gaussianKernelSize_valueChanged(int gaussianKernelSize)
{
    edl.setGaussianKernelSize(gaussianKernelSize);
}

void EDLConfigDialog::on_anchorThreshold_valueChanged(int anchorThreshold)
{
    edl.setAnchorThreshold(anchorThreshold);
}

void EDLConfigDialog::on_angleTolerance_valueChanged(double angleTolerance)
{
    edl.setAngleTolerance(angleTolerance * M_PI / 180.0);
}
