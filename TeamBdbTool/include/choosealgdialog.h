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

#ifndef CHOOSEALGDIALOG_H
#define CHOOSEALGDIALOG_H

#include <QDialog>

#include <linedetection/linedetectionalgorithm.h>
#include <linedetection/edl/edl.h>
#include <linedetection/edl2/edl2.h>
#include <linedetection/hough/hough.h>

namespace Ui
{
class ChooseALGDialog;
}

class ChooseALGDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseALGDialog(QWidget *parent = 0);
    ~ChooseALGDialog();

    formseher::LineDetectionAlgorithm *alg;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseALGDialog *ui;


};

#endif // CHOOSEALGDIALOG_H
