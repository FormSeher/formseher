#ifndef FS_ALGORITHMCONTROLWIDGET_H
#define FS_ALGORITHMCONTROLWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <map>

#include "linedetection/linedetectionalgorithm.h"
#include "linedetectionalgorithmconfigdialog.h"
#include "threading/algorithmcontroller.hpp"

namespace Ui {
class AlgorithmControlWidget;
}

namespace formseher
{

class AlgorithmControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmControlWidget(QWidget *parent = 0);
    ~AlgorithmControlWidget();

    bool registerAlgorithmConfigDialog(std::string id, LineDetectionAlgorithmConfigDialog* dialog);

    void setCvWindowName(const std::string &value);

private slots:
    void on_saveResult_clicked();
    void on_openPicture_clicked();
    void on_controller_newResultAvailable();
    void on_algorithmSelectBox_currentIndexChanged(const QString &algorithmId);
    void on_configureAlgorithm_clicked();
    void on_showWindowCheckBox_toggled(bool checked);

    void on_displayConfig_currentIndexChanged(int);

    void on_benchmarkButton_clicked();

private:
    void updateImageLabel();
    void updateResultImage();

    double getTime();

    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, LineDetectionAlgorithmConfigDialog*> algorithmConfigDialogs;
    LineDetectionAlgorithmConfigDialog* selectedAlgorithmDialog;
    AlgorithmController controller;

    std::vector<Line> latestResult;

    cv::Mat image;
    cv::Mat resultImage;
    std::string cvWindowName;
};

} // namespace formseher

#endif // FS_ALGORITHMCONTROLWIDGET_H
