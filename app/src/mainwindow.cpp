#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "algorithm.h"
#include "line.h"
#include "algorithmcontroller.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    algorithmControlWidgets[0] = ui->algorithmControlWidget1;
    algorithmControlWidgets[1] = ui->algorithmControlWidget2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::registerAlgorithmConfigDialog(int slot, std::string id, AlgorithmConfigDialog* dialog)
{
    if (slot < 1 || slot > 2)
        return false;

    return algorithmControlWidgets[slot - 1]->registerAlgorithmConfigDialog(id, dialog);
}
