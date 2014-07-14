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

#ifndef SAVEOBJECTDIALOG_H
#define SAVEOBJECTDIALOG_H

// Qt
#include <QDialog>

namespace Ui {
class SaveObjectDialog;
}

/**
 * @brief The Settings class is a Qt UI class wich represents the save object dialog.
 */
class SaveObjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief SaveObjectDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit SaveObjectDialog(QWidget *parent = 0);

    /**
     * @brief SaveObjectDialog destructor.
     */
    ~SaveObjectDialog();

    /**
     * @brief getObjectName Getter for the typed object name.
     * @return Typed objectname.
     */
    QString getObjectName() const;

private:
    Ui::SaveObjectDialog *ui;
};

#endif // SAVEOBJECTDIALOG_H
