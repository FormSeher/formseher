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

#ifndef OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
#define OBJECTDETECTIONALGORITHMTEAMBDIALOG_H

#include <QDialog>
#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"
#include "objectdetection/objectdetectionalgorithm.h"

namespace Ui {
class ObjectDetectionAlgorithmTeamBDialog;
}

namespace formseher
{
class ObjectDetectionAlgorithmTeamBDialog : public ObjectDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:

    /**
     * @brief ObjectDetectionAlgorithmTeamBDialog constructor.
     * @param parent Pointer to parent widget.
     */
    explicit ObjectDetectionAlgorithmTeamBDialog(QWidget *parent = 0);
    ~ObjectDetectionAlgorithmTeamBDialog();

    /*! @copydoc ObjectDetectionAlgorithm::calculate()
     */
    ObjectDetectionAlgorithm* createAlgorithm();

private slots:
    // These slots just trigger the AlgorithmConfigDialog.configChanged() signal.
    void on_minRating_valueChanged(int);
    void on_maxAngleThreshold_valueChanged(double);
    void on_maxDistanceThreshold_valueChanged(double);
    void on_midPointEnvironment_valueChanged(int);
    void on_fastMode_toggled(bool);

private:
    Ui::ObjectDetectionAlgorithmTeamBDialog *ui;
};
}

#endif // OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
