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

#ifndef FS_HOUGHCONFIGDIALOG_H
#define FS_HOUGHCONFIGDIALOG_H

#include <QDialog>

#include "gui/linedetection/linedetectionalgorithmconfigdialog.h"
#include "linedetection/hough/hough.h"

namespace Ui {
class HoughConfigDialog;
}

namespace formseher
{

/**
 * @brief The HoughConfigDialog class used to create EDL instances.
 */
class HoughConfigDialog : public LineDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:

    /**
     * @brief HoughConfigDialog constructor
     * @param parent Parent widget.
     */
    explicit HoughConfigDialog(QWidget *parent = 0);

    /**
     * @brief HoughConfigDialog destructor.
     */
    ~HoughConfigDialog();

    /**
     * @brief Create a new Hough instance with current parameters.
     * @return Algorithm pointer to an EDL instance.
     */
     LineDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_checkEnvironmentSize_valueChanged(int);
    void on_maximalLineGap_valueChanged(int);
    void on_minimumLineSize_valueChanged(int);

private:
    Ui::HoughConfigDialog *ui;

    Hough hough;
};

} // namespace formseher

#endif // FS_HOUGHCONFIGDIALOG_H

