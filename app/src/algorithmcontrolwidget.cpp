#include "algorithmcontrolwidget.h"
#include "ui_algorithmcontrolwidget.h"

#include <QImage>
#include <opencv2/imgproc/imgproc.hpp>

AlgorithmControlWidget::AlgorithmControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmControlWidget)
{
    ui->setupUi(this);
}

AlgorithmControlWidget::~AlgorithmControlWidget()
{
    delete ui;
}

void AlgorithmControlWidget::setCvMatrix(cv::InputArray _matrix)
{
    cv::Mat matrix = _matrix.getMat();
    cv::Mat converted = cv::Mat(matrix.rows, matrix.cols, matrix.type());
    cv::cvtColor(matrix, converted, CV_BGR2RGB);
    QImage qImage = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();

    QSize imageSize = qImage.size();
    imageSize.scale(ui->imageLabel->size(), Qt::KeepAspectRatio);
    QImage scaledImage = qImage.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
}
