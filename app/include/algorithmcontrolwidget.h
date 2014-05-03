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

    void setCvWindowName(const std::string &value);

private slots:
    void on_saveResult_clicked();
    void on_openPicture_clicked();
    void on_controller_newResultAvailable();
    void on_algorithmSelectBox_currentIndexChanged(const QString &algorithmId);
    void on_configureAlgorithm_clicked();
    void on_showWindowCheckBox_toggled(bool checked);

    void on_displayConfig_currentIndexChanged(int index);

private:
    void updateImageLabel();
    void updateResultImage();

    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
    AlgorithmConfigDialog* selectedAlgorithmDialog;
    AlgorithmController controller;

    std::vector<Line> latestResult;

    cv::Mat image;
    cv::Mat resultImage;
    std::string cvWindowName;
};

#endif // ALGORITHMCONTROLWIDGET_H
