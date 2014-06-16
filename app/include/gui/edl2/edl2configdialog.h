#ifndef FS_EDL2CONFIGDIALOG_H
#define FS_EDL2CONFIGDIALOG_H

#include <QDialog>

#include "gui/linedetectionalgorithmconfigdialog.h"
#include "linedetection/edl2/edl2.h"

namespace Ui {
class EDL2ConfigDialog;
}

namespace formseher
{

/**
 * @brief The EDL2ConfigDialog class used to create EDL2 instances.
 */
class EDL2ConfigDialog : public LineDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:
    /**
     * @brief EDL2ConfigDialog constructor
     * @param parent Parent widget.
     */
    explicit EDL2ConfigDialog(QWidget *parent = 0);

    /**
     * @brief EDLConfigDialog destructor.
     */
    ~EDL2ConfigDialog();

    /**
     * @brief Create a new EDL2 instance with current parameters.
     * @return Algorithm pointer to an EDL instance.
     */
    LineDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_gaussianKernelSize_valueChanged(int);
    void on_minAnchorThreshold_valueChanged(int);
    void on_anchorStepping_valueChanged(int);
    void on_anchorThreshold_valueChanged(int);
    void on_angleTolerance_valueChanged(double);
    void on_minLineLength_valueChanged(int);

private:
    Ui::EDL2ConfigDialog *ui;
};

} // namespace formseher

#endif // FS_EDL2CONFIGDIALOG_H
