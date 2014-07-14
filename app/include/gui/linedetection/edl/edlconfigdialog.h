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

#ifndef FS_EDLCONFIGDIALOG_H
#define FS_EDLCONFIGDIALOG_H

#include <QDialog>

#include "gui/linedetection/linedetectionalgorithmconfigdialog.h"
#include "linedetection/edl/edl.h"

namespace Ui {
class EDLConfigDialog;
}

namespace formseher
{

/**
 * @brief The EDLConfigDialog class used to create EDL instances.
 */
class EDLConfigDialog : public LineDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:
    /**
     * @brief EDLConfigDialog constructor
     * @param parent Parent widget.
     */
    explicit EDLConfigDialog(QWidget *parent = 0);

    /**
     * @brief EDLConfigDialog destructor.
     */
    ~EDLConfigDialog();

    /**
     * @brief Create a new EDL instance with current parameters.
     * @return Algorithm pointer to an EDL instance.
     */
    LineDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_sobelKernelSize_valueChanged(int);
    void on_sobelScale_valueChanged(double);
    void on_sobelDelta_valueChanged(double);
    void on_gaussianKernelSize_valueChanged(int);
    void on_anchorThreshold_valueChanged(int);
    void on_angleTolerance_valueChanged(double);
    void on_minLineLength_valueChanged(int);

private:
    Ui::EDLConfigDialog *ui;
};

} // namespace formseher

#endif // FS_EDLCONFIGDIALOG_H
