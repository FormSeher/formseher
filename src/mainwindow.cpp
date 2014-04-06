#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::addAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog *dialog)
{
    if(algorithmConfigDialogs.find(id) == algorithmConfigDialogs.end())
    {
        return false;
    }

    algorithmConfigDialogs[id] = dialog;
    return true;
}
