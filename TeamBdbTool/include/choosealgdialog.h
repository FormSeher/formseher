#ifndef CHOOSEALGDIALOG_H
#define CHOOSEALGDIALOG_H

#include <QDialog>

#include <linedetection/linedetectionalgorithm.h>
#include <linedetection/edl/edl.h>
#include <linedetection/edl2/edl2.h>
#include <linedetection/hough/hough.h>

namespace Ui
{
class ChooseALGDialog;
}

class ChooseALGDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseALGDialog(QWidget *parent = 0);
    ~ChooseALGDialog();

    formseher::LineDetectionAlgorithm *alg;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseALGDialog *ui;


};

#endif // CHOOSEALGDIALOG_H
