#include "algorithmcontrolwidget.h"
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
    ui->comboBox->addItem(QString(id.c_str()));

    return true;
}

void AlgorithmControlWidget::setCvMatrix(cv::InputArray _matrix)
{
    image = _matrix.getMat();
    cv::Mat converted = cv::Mat(image.rows, image.cols, image.type());
    cv::cvtColor(image, converted, CV_BGR2RGB);
    QImage qImage = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->imageLabel->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
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

        ui->lineEdit1->setText(fileName);
        setCvMatrix(cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR));

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
    // Random number generator for colorful lines
    cv::RNG rng(0xFFFFFFFF);

    cv::Mat resultMat = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);

    std::vector<Line> result = controller.getLatestResult();
    for(auto line : result)
    {
        cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::line(resultMat, line.getStart(), line.getEnd(), color);
    }
}
