#ifndef FS_ALGORITHMCONTROLWIDGET_H
#define FS_ALGORITHMCONTROLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <map>
#include <QColorDialog>

#include "linedetection/linedetectionalgorithm.h"
#include "linedetection/linedetectionalgorithmconfigdialog.h"
#include "objectdetection/objectdetectionalgorithm.h"
#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"
#include "threading/algorithmcontroller.hpp"

namespace Ui {
class AlgorithmControlWidget;
}

namespace formseher
{
class VideoInput;

class AlgorithmControlWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief AlgorithmControlWidget standard constructor.
     * @param parent Parent widget.
     */
    explicit AlgorithmControlWidget(QWidget *parent = 0);

    /**
     * AlgorithmControlWidget destructor.
     */
    ~AlgorithmControlWidget();

    /**
     * @brief Registers a LineDetectionAlgorithmConfigDialog.
     * @param id Id to identify the dialog.
     * @param dialog Pointer to instance of LineDetectionAlgorithmConfigDialog.
     * @return True if registration was successful.
     */
    bool registerLineAlgorithmConfigDialog(std::string id, LineDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Registers a ObjectDetectionAlgorithmCOnfigDialog.
     * @param id Id to identify the dialog.
     * @param dialog Pointer to instance of ObjectDetectionAlgorithmConfigDialog.
     * @return True if registration was successful.
     */
    bool registerObjectAlgorithmConfigDialog(std::string id, ObjectDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Set name of windows created by OpenCV.
     * @param value Name of the window.
     */
    void setCvWindowName(const std::string &value);

private slots:
    void on_saveResult_clicked();
    void on_openPicture_clicked();
    void on_controller_startedCalculation();
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

    void on_webcamRadioButton_clicked();

    void on_imageRadioButton_clicked();

    void on_objectBenchmarkButton_clicked();

    void on_linecolorButton_clicked();

    void on_objectcolorButton_clicked();

    void on_linecolorrandomcheckBox_clicked(bool checked);

    void on_objectcolorrandomcheckBox_clicked(bool checked);

    void on_statusUpdate(QString status);

    void on_lineThicknessBox_valueChanged(int);
    void on_objectLineThicknessBox_valueChanged(int);

signals:
    /**
     * @brief Emited to signal a status change.
     * @param statusString Description of the status change.
     */
    void statusUpdate(QString statusString);

private:
    /**
     * @brief Assigns the resultImage to the resultImageLabel.
     */
    void updateImageLabel();

    /**
     * @brief Draws result of last algorithms run to resultImage.
     */
    void updateResultImage();

    /**
     * @brief Returns current system time.
     * @return Current system time in ms.
     */
    double getTime();

    cv::Scalar randomcolor(QColor colorimput, int opt);

    Ui::AlgorithmControlWidget *ui;

    std::map<std::string, LineDetectionAlgorithmConfigDialog*> lineAlgorithmConfigDialogs;
    LineDetectionAlgorithmConfigDialog* selectedLineAlgorithmConfigDialog;
    std::map<std::string, ObjectDetectionAlgorithmConfigDialog*> objectAlgorithmConfigDialogs;
    ObjectDetectionAlgorithmConfigDialog* selectedObjectAlgorithmConfigDialog;
    AlgorithmController controller;

    std::vector<Model> models;

    algorithmworker_result latestResult;

    cv::Mat image;
    cv::Mat resultImage;
    std::string cvWindowName;

    VideoInput* webcam;
};

} // namespace formseher

#endif // FS_ALGORITHMCONTROLWIDGET_H
