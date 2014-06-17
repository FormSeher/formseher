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
    // Random number generator for colorful lines
    cv::RNG rng(0xFFFFFFFF);

    if(!ui->showOriginalCheckBox->isChecked())
        resultImage = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
    else
        resultImage = image.clone();


    if(ui->showLinesCheckBox->isChecked())
    {
        for(auto line : latestResult.first)
        {
            double color1, color2, color3;

                 color1 = rng.uniform(0, 255);
                 color2 = rng.uniform(0, 255);
                 color3 = rng.uniform(0, 255);

                 if(abs(color1-color2)<50 && abs(color1-color3)<50 && abs(color2-color3)<50)
                 {
                     if((color1+color2+color3) > 382)
                     {
                         switch(rng.uniform(0, 2))
                         {
                         case 0: color1 = 0;
                         case 1: color2 = 0;
                         case 2: color3 = 0;
                         }
                     }
                     else
                     {
                         switch(rng.uniform(0, 2))
                         {
                         case 0: color1 = 255;
                         case 1: color2 = 255;
                         case 2: color3 = 255;
                         }
                     }
                 }

             cv::Scalar color(color1, color2, color3);
            //cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            cv::line(resultImage, line.getStart(), line.getEnd(), color);
        }
    }

    if(ui->showObjectsCheckBox->isChecked())
    {
        for(auto object : latestResult.second)
        {
           double color1, color2, color3;

                color1 = rng.uniform(0, 255);
                color2 = rng.uniform(0, 255);
                color3 = rng.uniform(0, 255);

                if(abs(color1-color2)<50 && abs(color1-color3)<50 && abs(color2-color3)<50)
                {
                    if((color1+color2+color3) > 382)
                    {
                        switch(rng.uniform(0, 2))
                        {
                        case 0: color1 = 0;
                        case 1: color2 = 0;
                        case 2: color3 = 0;
                        }
                    }
                    else
                    {
                        switch(rng.uniform(0, 2))
                        {
                        case 0: color1 = 255;
                        case 1: color2 = 255;
                        case 2: color3 = 255;
                        }
                    }
                }

            cv::Scalar color(color1, color2, color3);
            //cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            // Draw bounding box
            cv::rectangle(resultImage,object.getBoundingBox(), color);
            // Draw lines of object
            for(auto line : object.getLines())
            {
                cv::line(resultImage, line->getStart(), line->getEnd(), color);
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
    std::vector<Model> models = dbu.read();
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

    LineDetectionAlgorithm* lines = selectedLineAlgorithmConfigDialog->createAlgorithm();
    ObjectDetectionAlgorithm* algorithm = selectedObjectAlgorithmConfigDialog->createAlgorithm();
    std::vector<formseher::Line> line = lines->calculate(image.clone());

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

/*    for(int i = 0; i < executionCount; ++i)
        algorithm->calculate(lines->calculate(image.clone()));
*/

    for(int i = 0; i < executionCount; ++i)
        algorithm->calculate(line);

    endTime = getTime();
    // End of time measurement

    double elapsedTime = endTime - startTime;

    ui->objectBenchmarkResult->setText(QString::number(elapsedTime / executionCount) + " s");
    benchmarkDialog.close();
}
