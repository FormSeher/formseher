#ifndef HOUGHCONFIGDIALOG_H
#define HOUGHCONFIGDIALOG_H

#include <QDialog>

#include "gui/algorithmconfigdialog.h"
#include "linedetection/hough/hough.h"

namespace Ui {
class HoughConfigDialog;
}

namespace formseher
{

/**
 * @brief The HoughConfigDialog class used to create EDL instances.
 */
class HoughConfigDialog : public AlgorithmConfigDialog
{
    Q_OBJECT

public:

    /**
     * @brief HoughConfigDialog constructor
     * @param parent Parent widget.
     */
    explicit HoughConfigDialog(QWidget *parent = 0);

    /**
     * @brief HoughConfigDialog destructor.
     */
    ~HoughConfigDialog();

    /**
     * @brief Create a new Hough instance with current parameters.
     * @return Algorithm pointer to an EDL instance.
     */
     Algorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_checkEnvironmentSize_valueChanged(int);
    void on_maximalLineGap_valueChanged(int);
    void on_minimumLineSize_valueChanged(int);

private:
    Ui::HoughConfigDialog *ui;

    Hough hough;
};

} // namespace formseher

#endif // HOUGHCONFIGDIALOG_H

