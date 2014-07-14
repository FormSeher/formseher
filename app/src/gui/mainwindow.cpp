/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

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

} // namespace formseher
