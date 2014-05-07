#include "gui/algorithmcontrolwidget.h"
#include "ui_algorithmcontrolwidget.h"

#include <QImage>
#include <QDir>
#include <QString>
#include <QFileDialog>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>



AlgorithmControlWidget::AlgorithmControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmControlWidget)
{
    ui->setupUi(this);

    connect(&controller, &AlgorithmController::newResultAvailable, this, &AlgorithmControlWidget::on_controller_newResultAvailable);
}

AlgorithmControlWidget::~AlgorithmControlWidget()
{
    delete ui;
}

bool AlgorithmControlWidget::registerAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog *dialog)
{
    // Only register if id is still free
    if(algorithmConfigDialogs.find(id) != algorithmConfigDialogs.end())
        return false;

    algorithmConfigDialogs[id] = dialog;
    ui->algorithmSelectBox->addItem(QString(id.c_str()));

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

    if(ui->displayConfig->currentIndex() == 1)
        resultImage = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
    else
        resultImage = image.clone();

    if(ui->displayConfig->currentIndex() != 0)
    {
        for(auto line : latestResult)
        {
            cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            cv::line(resultImage, line.getStart(), line.getEnd(), color);
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

        controller.setImage(cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_GRAYSCALE));
        controller.enqueueAlgorithm();
    }
    catch(int e)
    {
        std::cout << "Error: Could not open picture." << std::endl;
    }
}

void AlgorithmControlWidget::on_controller_newResultAvailable()
{
    latestResult = controller.getLatestResult();
    updateResultImage();
}

void AlgorithmControlWidget::on_algorithmSelectBox_currentIndexChanged(const QString &algorithmId)
{
    selectedAlgorithmDialog = algorithmConfigDialogs[algorithmId.toStdString()];
    controller.setAlgorithmConfigDialog(selectedAlgorithmDialog);
}

void AlgorithmControlWidget::on_configureAlgorithm_clicked()
{
    selectedAlgorithmDialog->show();
}

void AlgorithmControlWidget::on_showWindowCheckBox_toggled(bool checked)
{
    if(checked && !resultImage.empty())
        cv::imshow(cvWindowName, resultImage);
}

void AlgorithmControlWidget::on_displayConfig_currentIndexChanged(int index)
{
    updateResultImage();
}

double AlgorithmControlWidget::getTime()
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
        puts ("WARNING: Cannot read time using 'clock_gettime'!");

    return (double) ts.tv_sec + (double) ts.tv_nsec * 1e-9;
}

void AlgorithmControlWidget::on_benchmarkButton_clicked()
{
    if(resultImage.empty())
            return;

    Algorithm* algorithm = selectedAlgorithmDialog->createAlgorithm();

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
        algorithm->calculate(image);

    endTime = getTime();
    // End of time measurement

    double elapsedTime = endTime - startTime;

    ui->benchmarkResult->setText(QString::number(elapsedTime / executionCount) + " sec");
    benchmarkDialog.close();
}