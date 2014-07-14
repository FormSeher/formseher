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
#include "include/addlinedialog.h"
#include "ui_addlinedialog.h"

// Formseher project
#include "line.h"

AddLineDialog::AddLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Line");
}

AddLineDialog::~AddLineDialog()
{
    delete ui;
}

formseher::Line AddLineDialog::getLine()
{
    return formseher::Line(ui->spinBoxStartX->value(), ui->spinBoxStartY->value(),
                           ui->spinBoxEndX->value(), ui->spinBoxEndY->value());
}
