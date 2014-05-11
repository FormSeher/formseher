#ifndef EDLCONFIGDIALOG_H
#define EDLCONFIGDIALOG_H

#include <QDialog>

#include "gui/algorithmconfigdialog.h"
#include "linedetection/edl/edl.h"

namespace Ui {
class EDLConfigDialog;
}

/**
 * @brief The EDLConfigDialog class used to create EDL instances.
 */
class EDLConfigDialog : public AlgorithmConfigDialog
{
    Q_OBJECT

public:
    /**
     * @brief EDLConfigDialog constructor
     * @param parent Parent widget.
     */
    explicit EDLConfigDialog(QWidget *parent = 0);

    /**
     * @brief EDLConfigDialog destructor.
     */
    ~EDLConfigDialog();

    /**
     * @brief Create a new EDL instance with current parameters.
     * @return Algorithm pointer to an EDL instance.
     */
    Algorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_sobelKernelSize_valueChanged(int);
    void on_sobelScale_valueChanged(double);
    void on_sobelDelta_valueChanged(double);
    void on_gaussianKernelSize_valueChanged(int);
    void on_anchorThreshold_valueChanged(int);
    void on_angleTolerance_valueChanged(double);
    void on_minLineLength_valueChanged(int);

private:
    Ui::EDLConfigDialog *ui;
};

#endif // EDLCONFIGDIALOG_H
