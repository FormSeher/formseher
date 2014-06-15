#ifndef OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
#define OBJECTDETECTIONALGORITHMTEAMBDIALOG_H

#include <QDialog>

namespace Ui {
class ObjectDetectionAlgorithmTeamBDialog;
}

class ObjectDetectionAlgorithmTeamBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectDetectionAlgorithmTeamBDialog(QWidget *parent = 0);
    ~ObjectDetectionAlgorithmTeamBDialog();

private:
    Ui::ObjectDetectionAlgorithmTeamBDialog *ui;
};

#endif // OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
