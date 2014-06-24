#ifndef CHOOSEALGDIALOG_H
#define CHOOSEALGDIALOG_H

#include <QDialog>

#include <linedetection/linedetectionalgorithm.h>
#include <linedetection/edl/edl.h>
#include <linedetection/edl2/edl2.h>
#include <linedetection/hough/hough.h>

namespace Ui {
class ChooseALGDialog;
}

class ChooseALGDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseALGDialog(formseher::LineDetectionAlgorithm* lineDetecionAlgorithm ,QWidget *parent = 0);
    ~ChooseALGDialog();

    formseher::LineDetectionAlgorithm* lineDetecionAlgorithm;

private slots:
    void on_radioButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();



private:
    Ui::ChooseALGDialog *ui;

};

#endif // CHOOSEALGDIALOG_H
