#ifndef ALGORITHMCONTROLWIDGET_H
#define ALGORITHMCONTROLWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <map>

#include "algorithm.h"
#include "algorithmconfigdialog.h"
#include "algorithmcontroller.hpp"

namespace Ui {
class AlgorithmControlWidget;
}

class AlgorithmControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmControlWidget(QWidget *parent = 0);
    ~AlgorithmControlWidget();

    void setCvMatrix(cv::InputArray matrix);

private slots:
    void on_saveResult_clicked();

    void on_openPicture_clicked();

private:
    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
    AlgorithmConfigDialog* selectedAlgorithmDialog;
    AlgorithmController controller;
};

#endif // ALGORITHMCONTROLWIDGET_H
