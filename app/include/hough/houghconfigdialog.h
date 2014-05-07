#ifndef HOUGHCONFIGDIALOG_H
#define HOUGHCONFIGDIALOG_H

#include <QDialog>

#include "algorithmconfigdialog.h"
#include "linedetection/hough/hough.h"

namespace Ui {
class HoughConfigDialog;
}

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
    void on_checkEnvironmentSize_valueChanged(int checkEnvironmentSize);
    void on_maximalLineGap_valueChanged(int maximalLineGap);
    void on_minimumLineSize_valueChanged(int minimumLineSize);

private:
    Ui::HoughConfigDialog *ui;

    Hough hough;
};

#endif // HOUGHCONFIGDIALOG_H

