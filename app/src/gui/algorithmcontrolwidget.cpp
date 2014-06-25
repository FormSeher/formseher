#include "gui/algorithmcontrolwidget.h"
#include "ui_algorithmcontrolwidget.h"

#include <QImage>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "videoinput.h"
#include "objectdetection/object.h"
#include "objectdetection/databaseutils.h"

namespace formseher
{

int linerandstate = 1, objectrandstate = 1;
QColor linecolor = Qt::gray, objectcolor = Qt::gray;

AlgorithmControlWidget::AlgorithmControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmControlWidget),
    webcam(0)
{
    ui->setupUi(this);

    connect(&controller, &AlgorithmController::newResultAvailable, this, &AlgorithmControlWidget::on_controller_newResultAvailable);
}

AlgorithmControlWidget::~AlgorithmControlWidget()
{
    delete ui;
}

bool AlgorithmControlWidget::registerLineAlgorithmConfigDialog(std::string id, LineDetectionAlgorithmConfigDialog *dialog)
{
    // Only register if id is still free
    if(lineAlgorithmConfigDialogs.find(id) != lineAlgorithmConfigDialogs.end())
        return false;

    lineAlgorithmConfigDialogs[id] = dialog;
    ui->lineAlgorithmSelectBox->addItem(QString(id.c_str()));

    return true;
}

bool AlgorithmControlWidget::registerObjectAlgorithmConfigDialog(std::string id, ObjectDetectionAlgorithmConfigDialog *dialog)
{
    // Only register if id is still free
    if(objectAlgorithmConfigDialogs.find(id) != objectAlgorithmConfigDialogs.end())
        return false;

    objectAlgorithmConfigDialogs[id] = dialog;
    ui->objectAlgorithmSelectBox->addItem(QString(id.c_str()));

    return true;
}

void AlgorithmControlWidget::updateImageLabel()
{
    if(resultImage.empty())
            return;

    cv::Mat converted = cv::Mat(resultImage.rows, resultImage.cols, resultImage.type());
    cv::cvtColor(resultImage, converted, CV_BGR2RGB);
    QImage qImage = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->imageLabel->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void AlgorithmControlWidget::updateResultImage()
{
    /*
    // Random number generator for colorful lines
    cv::RNG rng(0xFFFFFFFF);
    */

    if(!ui->showOriginalCheckBox->isChecked())
        resultImage = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
    else
        resultImage = image.clone();


    if(ui->showLinesCheckBox->isChecked())
        {
            for(auto line : latestResult.first)
            {
                //cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));


                //randomfunction

                cv::line(resultImage, line.getStart(), line.getEnd(), randomcolor(linecolor,linerandstate));
            }
        }

    if(ui->showObjectsCheckBox->isChecked())
    {
        for(auto object : latestResult.second)
        {
            //cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));


            //randomfunction

            // Draw bounding box
            cv::rectangle(resultImage,object.getBoundingBox(), randomcolor(objectcolor,objectrandstate));
            // Draw lines of object
            for(auto line : object.getLines())
            {
                cv::line(resultImage, line->getStart(), line->getEnd(),randomcolor(linecolor,objectrandstate));
            }
        }
    }

    if(ui->showWindowCheckBox->checkState() == Qt::Checked)
        cv::imshow(cvWindowName, resultImage);
    updateImageLabel();
}



void AlgorithmControlWidget::setCvWindowName(const std::string &value)
{
    cvWindowName = value;
}


void AlgorithmControlWidget::on_saveResult_clicked()
{
    try
    {
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save"), QDir::homePath(), tr("Image files (*.png *.jpg *.bmp)"));
        ui->imageLabel->pixmap()->toImage().save(fileName);
    }
    catch(int e)
    {
        std::cerr << "Error: Could not save result." << std::endl;
    }
}

void AlgorithmControlWidget::on_openPicture_clicked()
{
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr("Image files (*.png *.jpg *.bmp)"));

        image = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);

        controller.setImage(image);
    }
    catch(int e)
    {
        std::cout << "Error: Could not open picture." << std::endl;
    }
}

void AlgorithmControlWidget::on_controller_newResultAvailable()
{
    latestResult = controller.getLatestResult();

    // Special stuff when using webcam
    if(webcam)
    {
        // Update this->image
        cv::Mat webcamImage = webcam->getLastImage();

        if(!webcamImage.empty())
            image = webcam->getLastImage();

        // Get a new image and update controller
        (*webcam) >> webcamImage;

        if(!webcamImage.empty())
            controller.setImage(webcamImage);
        else
            // disable video playback and reset radioButtons
            on_imageRadioButton_clicked();
    }

    updateResultImage();
    emit statusUpdate(QString("Found %1 lines and %2 objects.")
                      .arg(latestResult.first.size())
                      .arg(latestResult.second.size()));
}

void AlgorithmControlWidget::on_lineAlgorithmSelectBox_currentIndexChanged(const QString &algorithmId)
{
    selectedLineAlgorithmConfigDialog = lineAlgorithmConfigDialogs[algorithmId.toStdString()];
    controller.setLineAlgorithmConfigDialog(selectedLineAlgorithmConfigDialog);
}


void AlgorithmControlWidget::on_objectAlgorithmSelectBox_currentIndexChanged(const QString &algorithmId)
{
    selectedObjectAlgorithmConfigDialog = objectAlgorithmConfigDialogs[algorithmId.toStdString()];
    controller.setObjectAlgorithmConfigDialog(selectedObjectAlgorithmConfigDialog);
}


void AlgorithmControlWidget::on_configureLineAlgorithm_clicked()
{
    selectedLineAlgorithmConfigDialog->show();
}

void AlgorithmControlWidget::on_showWindowCheckBox_toggled(bool checked)
{
    if(checked && !resultImage.empty())
        cv::imshow(cvWindowName, resultImage);
}

/*
void AlgorithmControlWidget::on_displayConfig_currentIndexChanged(int)
{
    updateResultImage();
}
*/



double AlgorithmControlWidget::getTime()
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
        puts ("WARNING: Cannot read time using 'clock_gettime'!");

    return (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
}


cv::Scalar AlgorithmControlWidget::randomcolor(QColor colorimput, int opt)
{
    QColor color;

    if(opt == 0)
    {
        color = colorimput;
    }
    else
    {
        switch(rand() % 44)
        {
            case 0: color.setRgb(170,0,0);break;
            case 1: color.setRgb(0,85,0);break;
            case 2: color.setRgb(170,85,0);break;
            case 3: color.setRgb(0,170,0);break;
            case 4: color.setRgb(170,170,0);break;
            case 5: color.setRgb(0,255,0);break;
            case 6: color.setRgb(170,255,0);break;
            case 7: color.setRgb(0,0,127);break;
            case 8: color.setRgb(170,0,127);break;
            case 9: color.setRgb(0,85,127);break;
            case 10: color.setRgb(170,85,127);break;
            case 11: color.setRgb(0,170,127);break;
            case 12: color.setRgb(0,255,127);break;
            case 13: color.setRgb(170,255,127);break;
            case 14: color.setRgb(0,0,255);break;
            case 15: color.setRgb(170,0,255);break;
            case 16: color.setRgb(0,85,255);break;
            case 17: color.setRgb(170,85,255);break;
            case 18: color.setRgb(0,170,255);break;
            case 19: color.setRgb(170,170,255);break;
            case 20: color.setRgb(0,255,255);break;
            case 21: color.setRgb(170,255,255);break;
            case 22: color.setRgb(85,0,0);break;
            case 23: color.setRgb(255,0,0);break;
            case 24: color.setRgb(85,85,0);break;
            case 25: color.setRgb(255,85,0);break;
            case 26: color.setRgb(85,170,0);break;
            case 27: color.setRgb(255,170,0);break;
            case 28: color.setRgb(85,255,0);break;
            case 29: color.setRgb(255,255,0);break;
            case 30: color.setRgb(85,0,127);break;
            case 31: color.setRgb(255,0,127);break;
            case 32: color.setRgb(85,85,127);break;
            case 33: color.setRgb(255,85,127);break;
            case 34: color.setRgb(85,170,127);break;
            case 35: color.setRgb(255,170,127);break;
            case 36: color.setRgb(85,255,127);break;
            case 37: color.setRgb(255,255,127);break;
            case 38: color.setRgb(85,0,255);break;
            case 39: color.setRgb(255,0,255);break;
            case 40: color.setRgb(85,85,255);break;
            case 41: color.setRgb(255,85,255);break;
            case 42: color.setRgb(85,170,255);break;
            case 43: color.setRgb(255,170,255);break;
            case 44: color.setRgb(85,255,255);break;
        }
 }
    cv::Scalar scalarcolor(color.blue(),color.green(),color.red());
    return scalarcolor;
}


void AlgorithmControlWidget::on_lineBenchmarkButton_clicked()
{
    if(resultImage.empty())
            return;

    LineDetectionAlgorithm* algorithm = selectedLineAlgorithmConfigDialog->createAlgorithm();

    double startTime;
    double endTime;
    int executionCount = 100;

    // Open Dialog if Benchmarking starts
    QDialog benchmarkDialog;
    benchmarkDialog.setWindowTitle("Benchmarking..");
    benchmarkDialog.autoFillBackground();
    benchmarkDialog.resize(300,0);
    benchmarkDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
    benchmarkDialog.show();

    // Begin time measurement and execute algorithm n-times

    startTime = getTime();

    for(int i = 0; i < executionCount; ++i)
        algorithm->calculate(image.clone());

    endTime = getTime();
    // End of time measurement

    double elapsedTime = endTime - startTime;

    ui->lineBenchmarkResult->setText(QString::number(elapsedTime / executionCount) + " s");
    benchmarkDialog.close();
}

void AlgorithmControlWidget::on_showOriginalCheckBox_clicked()
{
    updateResultImage();
}


void AlgorithmControlWidget::on_showLinesCheckBox_clicked()
{
    updateResultImage();
}


void AlgorithmControlWidget::on_showObjectsCheckBox_clicked()
{
    updateResultImage();
}

void AlgorithmControlWidget::on_openDatabaseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open database"), QDir::homePath(), tr("Database file (*.json)"));
    DatabaseUtils dbu(fileName.toStdString());
    models = dbu.read();
    controller.setDatabaseModels(models);

    ui->databaseLabel->setText(fileName.left(5) + "..." + fileName.right(20));
    emit statusUpdate(QString("Read %1 models from database %2")
                      .arg(models.size())
                      .arg(fileName));
}

void AlgorithmControlWidget::on_configureObjectAlgorithm_clicked()
{
    selectedObjectAlgorithmConfigDialog->show();
}

void AlgorithmControlWidget::on_webcamRadioButton_clicked()
{
    if(webcam)
        return;

    webcam = new VideoInput(0);

    if(!webcam->isOpened())
    {
        delete webcam;
        webcam = 0;
        // Display error message and reset radio buttons.
        QMessageBox::warning(this, "Error opening webcam", "Could not open default webcam '0'.");
        ui->imageRadioButton->toggle();

        return;
    }

    cv::Mat webcamImage;
    (*webcam) >> webcamImage;

    if(!webcamImage.empty())
        controller.setImage(webcamImage);
}

void AlgorithmControlWidget::on_imageRadioButton_clicked()
{
    if(webcam)
    {
        delete webcam;
        webcam = 0;
    }
}

} // namespace formseher

void formseher::AlgorithmControlWidget::on_objectBenchmarkButton_clicked()
{
    if(resultImage.empty())
            return;

    LineDetectionAlgorithm* lineAlgorithm = nullptr;
    ObjectDetectionAlgorithm* objectAlgorithm = nullptr;
    std::vector<formseher::Line> lines;

    double startTime = 0;
    double elapsedTime = 0;
    int executionCount = 100;

    // Benchmark loop
    for(int i = 0; i < executionCount; ++i)
    {
        lineAlgorithm = selectedLineAlgorithmConfigDialog->createAlgorithm();
        objectAlgorithm = selectedObjectAlgorithmConfigDialog->createAlgorithm();
        objectAlgorithm->setModels(models);

        // Measure runtime
        startTime = getTime();

        lines = lineAlgorithm->calculate(image.clone());
        objectAlgorithm->calculate(lines);

        elapsedTime += getTime() - startTime;

        delete lineAlgorithm;
        delete objectAlgorithm;
    }

    ui->objectBenchmarkResult->setText(QString::number(elapsedTime / executionCount) + " s");
}


void formseher::AlgorithmControlWidget::on_linecolorButton_clicked()
{
        linecolor = QColorDialog::getColor(Qt::gray, this);
        ui->linecolorLabel->setPalette(linecolor);
        if(linerandstate == 0)
        AlgorithmControlWidget::updateResultImage();
}

void formseher::AlgorithmControlWidget::on_objectcolorButton_clicked()
{
        objectcolor = QColorDialog::getColor(Qt::gray, this);
        ui->objectcolorLabel->setPalette(objectcolor);
        if(objectrandstate == 0)
        AlgorithmControlWidget::updateResultImage();
}



void formseher::AlgorithmControlWidget::on_linecolorrandomcheckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->linecolorLabel->setText("random");
        linerandstate = 1;
        AlgorithmControlWidget::updateResultImage();
    }
    else
    {
        ui->linecolorLabel->setText("");
        linerandstate = 0;
        AlgorithmControlWidget::updateResultImage();
    }
}

void formseher::AlgorithmControlWidget::on_objectcolorrandomcheckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->objectcolorLabel->setText("random");
        objectrandstate = 1;
        AlgorithmControlWidget::updateResultImage();
    }
    else
    {
        ui->objectcolorLabel->setText("");
        objectrandstate = 0;
        AlgorithmControlWidget::updateResultImage();
    }
}

