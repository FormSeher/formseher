#ifndef EDLCONFIGDIALOG_H
#define EDLCONFIGDIALOG_H

#include <QDialog>

#include "algorithmconfigdialog.h"
#include "edl/edl.h"

namespace Ui {
class EDLConfigDialog;
}

class EDLConfigDialog : public AlgorithmConfigDialog
{
    Q_OBJECT

public:
    explicit EDLConfigDialog(QWidget *parent = 0);
    ~EDLConfigDialog();

    Algorithm* createAlgorithm();

private slots:
    void on_sobelKernelSize_valueChanged(int arg1);

    void on_sobelScale_valueChanged(double sobelScale);

    void on_sobelDelta_valueChanged(double sobelDelta);

    void on_gaussianKernelSize_valueChanged(int gaussianKernelSize);

    void on_anchorThreshold_valueChanged(int anchorThreshold);

    void on_angleTolerance_valueChanged(double angleTolerance);

private:
    Ui::EDLConfigDialog *ui;
};

#endif // EDLCONFIGDIALOG_H
