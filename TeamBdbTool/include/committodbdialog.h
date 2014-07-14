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

#ifndef COMMITTODBDIALOG_H
#define COMMITTODBDIALOG_H

#include <QDialog>

#include <objectdetection/databaseutils.h>

namespace Ui
{
class commitToDBDialog;
}

class commitToDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit commitToDBDialog(formseher::Object obj, QString dbFile, QWidget *parent = 0);
    ~commitToDBDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::commitToDBDialog *ui;
    formseher::Object obj;
    QString dbFile;
};

#endif // COMMITTODBDIALOG_H
