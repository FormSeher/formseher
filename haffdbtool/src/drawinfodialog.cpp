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
#include "include/drawinfodialog.h"
#include "ui_drawinfodialog.h"

bool DrawInfoDialog::showEverytime = true;

DrawInfoDialog::DrawInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawInfoDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Drawing Note");

    ui->checkBoxShow->setChecked(DrawInfoDialog::showEverytime);

    // Slot connection
    connect(ui->checkBoxShow, SIGNAL(toggled(bool)), this, SLOT(slot_toggleShow(bool)));
}

DrawInfoDialog::~DrawInfoDialog()
{
    delete ui;
}

void DrawInfoDialog::slot_toggleShow(bool value)
{
    showEverytime = value;
}

int DrawInfoDialog::exec()
{
    if( ! DrawInfoDialog::showEverytime )
        return QDialog::Accepted;
    else
        return QDialog::exec();
}
