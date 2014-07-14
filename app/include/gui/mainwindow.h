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

#ifndef FS_MAINWINDOW_H
#define FS_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <string>

#include "gui/linedetection/linedetectionalgorithmconfigdialog.h"
#include "threading/algorithmcontroller.hpp"
#include "algorithmcontrolwidget.h"

namespace Ui {
class MainWindow;
}

namespace formseher
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow standard constructor.
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * MainWindow destructor.
     */
    ~MainWindow();

    /**
     * @brief Registers a LineDetectionAlgorithmConfigDialog.
     * @param slot Specify if dialog is assigned to left (0) or right (1) AlgorithmControlWidget.
     * @param id Id of the config dialog.
     * @param dialog Pointer to dialog instance.
     * @return Return if registration was successful.
     */
    bool registerLineAlgorithmConfigDialog(int slot, std::string id, LineDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Registers a ObjectDetectionAlgorithmConfigDialog.
     * @param slot Specify if dialog is assigned to left (0) or right (1) AlgorithmControlWidget.
     * @param id Id of the config dialog.
     * @param dialog Pointer to dialog instance.
     * @return Return if registration was successful.
     */
    bool registerObjectAlgorithmConfigDialog(int slot, std::string id, ObjectDetectionAlgorithmConfigDialog* dialog);

private:
    Ui::MainWindow *ui;

    AlgorithmControlWidget* algorithmControlWidgets[2];
};

} // namespace formseher

#endif // FS_MAINWINDOW_H
