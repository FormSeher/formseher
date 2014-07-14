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

#ifndef ADDLINEDIALOG_H
#define ADDLINEDIALOG_H

// Formseher project
#include "line.h"

// Qt
#include <QDialog>

namespace Ui {
class AddLineDialog;
}

/**
 * @brief The AddLineDialog class is a Qt UI class which
 * represents a widget to add a line based on two coordinates.
 */
class AddLineDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief AddLineDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit AddLineDialog(QWidget *parent = 0);

    /**
     * @brief AddLineDialog destructor.
     */
    ~AddLineDialog();

    /**
     * @brief getLine Getter function for the constructed line.
     * @return Constructed Line.
     */
    formseher::Line getLine();

private:
    Ui::AddLineDialog *ui;
};

#endif // ADDLINEDIALOG_H
