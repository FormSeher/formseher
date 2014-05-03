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

    bool registerAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog* dialog);

private slots:
    void on_saveResult_clicked();
    void on_openPicture_clicked();
    void on_controller_newResultAvailable();

    void on_algorithmSelectBox_currentIndexChanged(const QString &algorithmId);

    void on_configureAlgorithm_clicked();

private:
    void setCvMatrix(cv::InputArray matrix);

    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
    AlgorithmConfigDialog* selectedAlgorithmDialog;
    AlgorithmController controller;

    cv::Mat image;
};

#endif // ALGORITHMCONTROLWIDGET_H
