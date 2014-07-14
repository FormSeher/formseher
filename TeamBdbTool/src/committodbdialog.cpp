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

#include "committodbdialog.h"
#include "ui_committodbdialog.h"

commitToDBDialog::commitToDBDialog(formseher::Object obj, QString dbFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commitToDBDialog),
    obj(obj),
    dbFile(dbFile)
{
    ui->setupUi(this);

    //work the string for better output
    QString str = QString::fromStdString(obj.toString());
    str.replace(":", ":\n");
    str.replace(";", "\n");

    ui->textBrowser->setText(str);
}

commitToDBDialog::~commitToDBDialog()
{
    delete ui;
}

void commitToDBDialog::on_buttonBox_accepted()
{
     formseher::DatabaseUtils dbu(dbFile.toStdString());

     dbu.read(); //call read before we write

     dbu.addObject(obj);
     dbu.write();
}
