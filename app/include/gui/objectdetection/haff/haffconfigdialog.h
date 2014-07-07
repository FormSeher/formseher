#ifndef FS_HAFFCONFIGDIALOG_H
#define FS_HAFFCONFIGDIALOG_H

#include <QDialog>

#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

namespace Ui {
class HaffConfigDialog;
}

namespace formseher
{

class ObjectDetectionAlgorithm;

/**
 * @brief The HaffConfigDialog class used to create Haff instances.
 */
class HaffConfigDialog : public ObjectDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:
    /**
     * @brief HaffConfigDialog constructor.
     * @param parent Pointer to parent widget.
     */
    explicit HaffConfigDialog(QWidget *parent = 0);

    /**
     * HaffConfigDialog destructor.
     */
    ~HaffConfigDialog();

    /*! @copydoc ObjectDetectionAlgorithm::calculate()
     */
    ObjectDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_numberOfBestHypotheses_valueChanged(int);
    void on_numberOfDetectedObjects_valueChanged(int);
    void on_minimalObjectRating_valueChanged(double);
    void on_coverWeight_valueChanged(double);
    void on_angleWeight_valueChanged(double);
    void on_positionWeight_valueChanged(double);

private:
    Ui::HaffConfigDialog *ui;
};

} // namespace formseher

#endif // FS_HAFFCONFIGDIALOG_H
