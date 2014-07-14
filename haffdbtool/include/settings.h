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

#ifndef SETTINGS_H
#define SETTINGS_H

// Formseher project
#include "linedetection/linedetectionalgorithm.h"

// Qt
#include <QMainWindow>

namespace Ui {
class Settings;
}

/**
 * @brief The Settings class is a Qt UI class wich represents the settings dialog.
 */
class Settings : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Settings standard constructor.
     * @param parent Parent widget.
     */
    explicit Settings(QWidget *parent = 0);

    /**
     * @brief Settings destructor.
     */
    ~Settings();

signals:
    /**
     * @brief signal_newSettings Signal that gets emmited if new settings get saved.
     */
    void signal_newSettings(formseher::LineDetectionAlgorithm*, std::pair<QColor, QColor>, int);

public slots:
    /**
     * @brief slot_settingsChanged Slot that gets connected to the accept/deny button in settings dialog.
     */
    void slot_settingsChanged();

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
