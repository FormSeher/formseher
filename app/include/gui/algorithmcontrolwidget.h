#ifndef FS_ALGORITHMCONTROLWIDGET_H
#define FS_ALGORITHMCONTROLWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <map>

#include "linedetection/linedetectionalgorithm.h"
#include "linedetectionalgorithmconfigdialog.h"
#include "objectdetection/objectdetectionalgorithm.h"
#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"
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

    bool registerLineAlgorithmConfigDialog(std::string id, LineDetectionAlgorithmConfigDialog* dialog);
    bool registerObjectAlgorithmConfigDialog(std::string id, ObjectDetectionAlgorithmConfigDialog* dialog);

    void setCvWindowName(const std::string &value);

private slots:
    void on_saveResult_clicked();
    void on_openPicture_clicked();
    void on_controller_newResultAvailable();
    void on_lineAlgorithmSelectBox_currentIndexChanged(const QString &algorithmId);
    void on_configureLineAlgorithm_clicked();
    void on_showWindowCheckBox_toggled(bool checked);

    void on_lineBenchmarkButton_clicked();

    void on_objectAlgorithmSelectBox_currentIndexChanged(const QString &arg1);

    void on_showOriginalCheckBox_clicked();

    void on_showLinesCheckBox_clicked();

    void on_showObjectsCheckBox_clicked();

    void on_openDatabaseButton_clicked();

    void on_configureObjectAlgorithm_clicked();

signals:
    void statusUpdate(QString statusString);

private:
    void updateImageLabel();
    void updateResultImage();

    double getTime();

    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, LineDetectionAlgorithmConfigDialog*> lineAlgorithmConfigDialogs;
    LineDetectionAlgorithmConfigDialog* selectedLineAlgorithmConfigDialog;
    std::map<std::string, ObjectDetectionAlgorithmConfigDialog*> objectAlgorithmConfigDialogs;
    ObjectDetectionAlgorithmConfigDialog* selectedObjectAlgorithmConfigDialog;
    AlgorithmController controller;

    algorithmworker_result latestResult;

    cv::Mat image;
    cv::Mat resultImage;
    std::string cvWindowName;
};

} // namespace formseher

#endif // FS_ALGORITHMCONTROLWIDGET_H
