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

#ifndef FS_HAFFCONFIGDIALOG_H
#define FS_HAFFCONFIGDIALOG_H

#include <QDialog>

#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

namespace Ui {
class HaffConfigDialog;
}

namespace formseher
{

class ObjectDetectionAlgorithm;

/**
 * @brief The HaffConfigDialog class used to create Haff instances.
 */
class HaffConfigDialog : public ObjectDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:
    /**
     * @brief HaffConfigDialog constructor.
     * @param parent Pointer to parent widget.
     */
    explicit HaffConfigDialog(QWidget *parent = 0);

    /**
     * HaffConfigDialog destructor.
     */
    ~HaffConfigDialog();

    /*! @copydoc ObjectDetectionAlgorithm::calculate()
     */
    ObjectDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_numberOfBestHypotheses_valueChanged(int);
    void on_numberOfDetectedObjects_valueChanged(int);
    void on_minimalObjectRating_valueChanged(double);
    void on_coverWeight_valueChanged(double);
    void on_angleWeight_valueChanged(double);
    void on_positionWeight_valueChanged(double);

private:
    Ui::HaffConfigDialog *ui;
};

} // namespace formseher

#endif // FS_HAFFCONFIGDIALOG_H
