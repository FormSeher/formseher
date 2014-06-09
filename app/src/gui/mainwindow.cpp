#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "line.h"
#include "threading/algorithmcontroller.hpp"

namespace formseher
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    algorithmControlWidgets[0] = ui->algorithmControlWidget1;
    algorithmControlWidgets[1] = ui->algorithmControlWidget2;

    algorithmControlWidgets[0]->setCvWindowName("Algorithm 1");
    algorithmControlWidgets[1]->setCvWindowName("Algorithm 2");

    connect(algorithmControlWidgets[0], &AlgorithmControlWidget::statusUpdate,
            this, &MainWindow::updateStatusBar);
    connect(algorithmControlWidgets[1], &AlgorithmControlWidget::statusUpdate,
            this, &MainWindow::updateStatusBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
bool MainWindow::registerAlgorithmConfigDialog(int slot, std::string id, LineDetectionAlgorithmConfigDialog* dialog)
{
    if (slot < 1 || slot > 2)
        return false;

    return algorithmControlWidgets[slot - 1]->registerAlgorithmConfigDialog(id, dialog);
}

} // namespace formseher
*/


bool MainWindow::registerLineAlgorithmConfigDialog(int slot, std::string id, LineDetectionAlgorithmConfigDialog* dialog)
{
    if (slot < 1 || slot > 2)
        return false;

    return algorithmControlWidgets[slot - 1]->registerLineAlgorithmConfigDialog(id, dialog);
}

bool MainWindow::registerObjectAlgorithmConfigDialog(int slot, std::string id, ObjectDetectionAlgorithmConfigDialog* dialog)
{
    if (slot < 1 || slot > 2)
        return false;

    return algorithmControlWidgets[slot - 1]->registerObjectAlgorithmConfigDialog(id, dialog);
}

void MainWindow::updateStatusBar(QString statusString)
{
    statusBar()->showMessage(statusString);
}

} // namespace formseher
