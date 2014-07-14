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

#ifndef FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H
#define FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H

#include <QDialog>

namespace formseher
{

class ObjectDetectionAlgorithm;

/**
 * @brief The ObjectDetectionAlgorithmConfigDialog class used to configure an ObjectDetectionAlgorithm.
 *
 * Each ObjectDetectionAlgorithm is shipped with an custom ObjectDetectionAlgorithmConfigDialog. This dialog
 * works as a factory which creates new ObjectDetectionAlgorithm instances.
 */
class ObjectDetectionAlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Standard ctor
     * @param parent
     */
    explicit ObjectDetectionAlgorithmConfigDialog(QWidget *parent = 0);

    /**
     * @brief Create a new ObjectDetectionAlgorithm instance.
     *
     * This is a factory method which creates a new ObjectDetectionAlgorithm instance
     * with the currently configured parameters.
     *
     * @return Pointer to the new ObjectDetectionAlgorithm.
     */
    virtual ObjectDetectionAlgorithm* createAlgorithm() = 0;

signals:
    /**
     * Emit this signal if the configuration was changed.
     */
    void configChanged();
};

} // namespace formseher

#endif // FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H
