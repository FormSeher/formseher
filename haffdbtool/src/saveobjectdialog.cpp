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

// Database tool
#include "include/saveobjectdialog.h"
#include "ui_saveobjectdialog.h"

SaveObjectDialog::SaveObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveObjectDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Save object");
}

SaveObjectDialog::~SaveObjectDialog()
{
    delete ui;
}

QString SaveObjectDialog::getObjectName() const
{
    return ui->lineEditObjectName->text();
}
