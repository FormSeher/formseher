#ifndef OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
#define OBJECTDETECTIONALGORITHMTEAMBDIALOG_H

#include <QDialog>
#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"
#include "objectdetection/objectdetectionalgorithm.h"

namespace Ui {
class ObjectDetectionAlgorithmTeamBDialog;
}

namespace formseher
{
class ObjectDetectionAlgorithmTeamBDialog : public ObjectDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:

    /**
     * @brief ObjectDetectionAlgorithmTeamBDialog constructor.
     * @param parent Pointer to parent widget.
     */
    explicit ObjectDetectionAlgorithmTeamBDialog(QWidget *parent = 0);
    ~ObjectDetectionAlgorithmTeamBDialog();

    /*! @copydoc ObjectDetectionAlgorithm::calculate()
     */
    ObjectDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_minRating_valueChanged(int);
    void on_maxAngleThreshold_valueChanged(double);
    void on_maxDistanceThreshold_valueChanged(double);
    void on_midPointEnvironment_valueChanged(int);
    void on_fastMode_toggled(bool);

private:
    Ui::ObjectDetectionAlgorithmTeamBDialog *ui;
};
}

#endif // OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
