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

#ifndef FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H
#define FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H

#include <QDialog>

namespace formseher
{

class LineDetectionAlgorithm;

/**
 * @brief The AlgorithmConfigDialog class used to configure an algorithm.
 *
 * Each algorithm is shipped with an custom AlgorithmConfigDialog. This dialog
 * works as a factory which creates new Algorithm instances.
 */
class LineDetectionAlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Standard ctor
     * @param parent
     */
    explicit LineDetectionAlgorithmConfigDialog(QWidget *parent = 0);

    /**
     * @brief Create a new Algorithm instance.
     *
     * This is a factory method which creates a new Algorithm instance
     * with the currently configured parameters.
     *
     * @return Pointer to the new Algorithm.
     */
    virtual LineDetectionAlgorithm* createAlgorithm() = 0;

signals:
    /**
     * Emit this signal if the configuration was changed.
     */
    void configChanged();

public slots:

};

} // namespace formseher

#endif // FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H
