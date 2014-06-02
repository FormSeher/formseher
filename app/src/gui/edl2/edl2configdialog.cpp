#include "gui/edl2/edl2configdialog.h"
#include "ui_edl2configdialog.h"
#include "mathutil.h"

namespace formseher
{

EDL2ConfigDialog::EDL2ConfigDialog(QWidget *parent) :
    LineDetectionAlgorithmConfigDialog(parent),
    ui(new Ui::EDL2ConfigDialog)
{
    ui->setupUi(this);
}

EDL2ConfigDialog::~EDL2ConfigDialog()
{
    delete ui;
}

LineDetectionAlgorithm* EDL2ConfigDialog::createAlgorithm()
{
    return new EDL2(
        ui->gaussianKernelSize->value(),
        ui->minAnchorThreshold->value(),
        ui->anchorStepping->value(),
        ui->anchorThreshold->value(),
        ui->angleTolerance->value() * math::m_pi / 180.0,
        ui->minLineLength->value()
    );
}

void EDL2ConfigDialog::on_minAnchorThreshold_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_anchorStepping_valueChanged(double)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_gaussianKernelSize_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_anchorThreshold_valueChanged(int)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_angleTolerance_valueChanged(double)
{
    emit configChanged();
}

void EDL2ConfigDialog::on_minLineLength_valueChanged(int)
{
    emit configChanged();
}

} // namespace formseher
