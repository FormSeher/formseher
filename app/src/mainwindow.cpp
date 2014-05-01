#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "algorithm.h"
#include "line.h"

QString safepath = "C:/Users/schwa_000/Desktop/studium neu/Projekt 2/bilder";

QString fileName;
cv::Mat cvimage1;
cv::Mat cvimage2;
QImage oimage1;
QImage oimage2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selectedAlgorithmDialog(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//functions:

QImage Mat2QImage(cv::Mat &mat, QImage::Format format){
    //cv::cvtColor(tmpImage, image, CV_BGR2RGB);
    //return QImage((const unsigned char*)(cvimage.data),cvimage.cols,cvimage.rows,QImage::Format_RGB888);
    return QImage(mat.data, mat.cols, mat.rows, mat.step, format);
}

cv::Mat QImage2Mat(QImage &img, int format){
    return cv::Mat(img.height(),img.width(),format,img.bits(),img.bytesPerLine());
}


void bigwindow(cv::Mat cvimage)
{
        cv::namedWindow("Großansicht");
        cv::imshow("Großansicht", cvimage);
        cv::waitKey(0);

}



//Mainblock:
bool MainWindow::registerAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog* dialog)
{
    // Only register if id is still free
    if(algorithmConfigDialogs.find(id) != algorithmConfigDialogs.end())
        return false;

    algorithmConfigDialogs[id] = dialog;
    ui->comboBox->addItem(QString(id.c_str()));

    return true;
}

void MainWindow::on_openpicture1_clicked()
{
    try
    {
    fileName = QFileDialog::getOpenFileName(this,
        tr("Bild 1 auswählen"), "C:/Users/schwa_000/Desktop/studium neu/Projekt 2/bilder", tr("Bild Dateien (*.png *.jpg *.bmp)"));

        ui->lineEdit1->setText(fileName);

        cvimage1 = cv::imread(fileName.toStdString(),1);
        oimage1.load(fileName);

        QSize pixSize = oimage1.size();
        pixSize.scale(ui->labelview1->size(),Qt::KeepAspectRatio);
        QImage scaledPic = oimage1.scaled(pixSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        ui->labelview1->setPixmap(QPixmap::fromImage(scaledPic));
    }
    catch(int e)
    {
    printf("Fehler beim Einlesen der Bild1 Datei");
    }
}


void MainWindow::on_openpicture2_clicked()
{
    try
    {
    fileName = QFileDialog::getOpenFileName(this,
        tr("Bild 2 auswählen"), safepath, tr("Bild Dateien (*.png *.jpg *.bmp)"));

        ui->lineEdit2->setText(fileName);

        cvimage2 = cv::imread(fileName.toStdString(),1);
        oimage2.load(fileName);

        QSize pixSize = oimage2.size();
        pixSize.scale(ui->labelview2->size(),Qt::KeepAspectRatio);
        QImage scaledPic = oimage2.scaled(pixSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        ui->labelview2->setPixmap(QPixmap::fromImage(scaledPic));
    }
    catch(int e)
    {
    printf("Fehler beim Einlesen der Bild2 Datei");
    }
}



void MainWindow::on_save1_clicked()
{
    try
    {
    fileName = QFileDialog::getSaveFileName(this,tr("Speicherort wählen"), safepath, tr("Bild Dateien (*.png *.jpg *.bmp)"));

    oimage1.save(fileName);
    }
    catch(int e)
    {
    printf("Fehler beim Speichern von Bild1");
    }
}


void MainWindow::on_save2_clicked()
{
    try
    {
    fileName = QFileDialog::getSaveFileName(this,tr("Speicherort wählen"), safepath, tr("Bild Dateien (*.png *.jpg *.bmp)"));

    oimage2.save(fileName);
    }
    catch(int e)
    {
    printf("Fehler beim Speichern von Bild2");
    }
}


void MainWindow::on_lineEdit1_returnPressed()
{
    try
    {
    oimage1.load(ui->lineEdit1->text());
    cvimage1 = cv::imread(ui->lineEdit1->text().toStdString(),1);

    QSize pixSize = oimage1.size();
    pixSize.scale(ui->labelview1->size(),Qt::KeepAspectRatio);
    QImage scaledPic = oimage1.scaled(pixSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->labelview1->setPixmap(QPixmap::fromImage(scaledPic));
    }
    catch(int e)
    {
    printf("Ungültige Eingabe.");
    }
}


void MainWindow::on_lineEdit2_returnPressed()
{
    try
    {
    oimage2.load(ui->lineEdit1->text());
    cvimage2 = cv::imread(ui->lineEdit2->text().toStdString(),1);

    QSize pixSize = oimage2.size();
    pixSize.scale(ui->labelview2->size(),Qt::KeepAspectRatio);
    QImage scaledPic = oimage2.scaled(pixSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->labelview2->setPixmap(QPixmap::fromImage(scaledPic));
    }
    catch(int e)
    {
    printf("Ungültige Eingabe.");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
   bigwindow(cvimage1);
}

void MainWindow::on_pushButton_4_clicked()
{
   bigwindow(cvimage2);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &algorithmId)
{
    selectedAlgorithmDialog = algorithmConfigDialogs[algorithmId.toStdString()];
    worker1.setAlgorithmConfigDialog(selectedAlgorithmDialog);
}

void MainWindow::on_pushButton_clicked()
{
    selectedAlgorithmDialog->show();
}
