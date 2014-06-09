#include "include/imagewidget.h"
#include "ui_imagewidget.h"
#include "linedetection/edl/edl.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

#include <QFile>
#include <QMessageBox>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);

    ui->imageModeBox->addItem(QString::fromStdString(MODE_GREY_LINES));
    ui->imageModeBox->addItem(QString::fromStdString(MODE_IMG_LINES));
    ui->imageModeBox->addItem(QString::fromStdString(MODE_LINES));
    ui->imageModeBox->addItem(QString::fromStdString(MODE_GREY));
    ui->imageModeBox->addItem(QString::fromStdString(MODE_IMG));

    connect(this, SIGNAL(imageChanged()), this, SLOT(imageChangedActions()));
    connect(ui->reloadButton, SIGNAL(clicked()), this, SLOT(imageChangedActions()));
    connect(ui->imageModeBox, SIGNAL(currentTextChanged(QString)), this, SLOT(imageChangedActions()));
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::setImage(QString imagePath, cv::Mat& image)
{
    image.copyTo(originalImage);
    ui->imagePathLabel->setText(imagePath);
    emit imageChanged();
}

void ImageWidget::imageChangedActions()
{
    QFile file( ui->imagePathLabel->text() );
    if( file.exists() )
    {
        cv::cvtColor(originalImage, greyImage, CV_BGR2GRAY);
        ui->reloadButton->setEnabled(true);
        emit imageModeChanged();
    }
    else
    {
        //QMessageBox::StandardButton msg;
        QMessageBox::critical(this, "Error!", "No valid image loaded!");
    }
}


void ImageWidget::setImageToLabel()
{

    cv::Mat converted;
    if( ui->imageModeBox->currentText().toStdString() == MODE_GREY || ui->imageModeBox->currentText().toStdString() == MODE_GREY_LINES)
    {
        converted = cv::Mat(greyImage.rows, greyImage.cols, greyImage.type());
        cv::cvtColor(greyImage, converted, CV_GRAY2RGB);
    }
    else if( ui->imageModeBox->currentText().toStdString() == MODE_IMG || ui->imageModeBox->currentText().toStdString() == MODE_IMG_LINES)
    {
        converted = cv::Mat(originalImage.rows, originalImage.cols, originalImage.type());
        cv::cvtColor(originalImage, converted, CV_BGR2RGB);
    }
    else
    {
        converted = cv::Mat::zeros(originalImage.rows, originalImage.cols, originalImage.type());
        //cv::Mat::zeros(cv::cvtColor(converted, converted, CV_BGR2RGB);
    }

    QImage qImage = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->imageLabel->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void ImageWidget::repaintImage(std::vector<formseher::Line> selectedLines, formseher::Line selectedLine,
                  QColor defaultColor, QColor selectedColor)
{

    cv::Mat converted;
    if( ui->imageModeBox->currentText().toStdString() == MODE_GREY || ui->imageModeBox->currentText().toStdString() == MODE_GREY_LINES)
    {
        converted = cv::Mat(greyImage.rows, greyImage.cols, greyImage.type());
        cv::cvtColor(greyImage, converted, CV_GRAY2RGB);
    }
    else if( ui->imageModeBox->currentText().toStdString() == MODE_IMG || ui->imageModeBox->currentText().toStdString() == MODE_IMG_LINES)
    {
        converted = cv::Mat(originalImage.rows, originalImage.cols, originalImage.type());
        cv::cvtColor(originalImage, converted, CV_BGR2RGB);
    }
    else
    {
        converted = cv::Mat::zeros(originalImage.rows, originalImage.cols, originalImage.type());
        //cv::Mat::zeros(cv::cvtColor(converted, converted, CV_BGR2RGB);
    }

    if( ui->imageModeBox->currentText().toStdString() == MODE_LINES       ||
        ui->imageModeBox->currentText().toStdString() == MODE_IMG_LINES   ||
        ui->imageModeBox->currentText().toStdString() == MODE_GREY_LINES  )
    {
        for(auto line: selectedLines)
        {
            cv::line(converted, line.getStart(), line.getEnd(), cv::Scalar(defaultColor.red(), defaultColor.green(), defaultColor.blue()));
        }

        cv::line(converted, selectedLine.getStart(), selectedLine.getEnd(), cv::Scalar(selectedColor.red(), selectedColor.green(), selectedColor.blue()));
    }

    QImage qImage = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->imageLabel->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}
