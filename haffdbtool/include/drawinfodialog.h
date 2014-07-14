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

#ifndef DRAWINFODIALOG_H
#define DRAWINFODIALOG_H

// Qt
#include <QDialog>

namespace Ui {
class DrawInfoDialog;
}

/**
 * @brief The DrawInfoDialog class is a Qt UI class which
 * displays a dialog with information about drawing.
 */
class DrawInfoDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DrawInfoDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit DrawInfoDialog(QWidget *parent = 0);

    /**
     * @brief DrawInfoDialog destructor.
     */
    ~DrawInfoDialog();

    /**
     * @brief exec Overload of the QDialog exec function.
     * @return Return if the dialog got accepted.
     */
    virtual int exec();

private slots:
    /**
     * @brief slot_toggleShow Slot that gets connected to the "Show everytime" checkbox.
     * @param value Indication if "Show everytime" is checked.
     */
    void slot_toggleShow(bool value);

private:
    Ui::DrawInfoDialog *ui;

    /** @brief showEverytime Hold the value of the "Show everytime" checkbox. */
    static bool showEverytime;
};

#endif // DRAWINFODIALOG_H
