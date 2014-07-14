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

#include "threading/algorithmcontroller.hpp"

#include <opencv2/imgproc/imgproc.hpp>

#include "gui/linedetection/linedetectionalgorithmconfigdialog.h"
#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

#include "threading/algorithmworker.h"

#include "linedetection/linedetectionalgorithm.h"
#include "objectdetection/objectdetectionalgorithm.h"

namespace formseher
{

AlgorithmController::AlgorithmController()
    : lineConfigDialog(0),
      objectConfigDialog(0)
{
    queuedAlgorithms.first = 0;
    queuedAlgorithms.second = 0;
    scheduledAlgorithms.first = 0;
    scheduledAlgorithms.second = 0;
}

AlgorithmController::~AlgorithmController()
{
    if(queuedAlgorithms.first)
        delete queuedAlgorithms.first;
    if(queuedAlgorithms.second)
        delete queuedAlgorithms.second;
}

void AlgorithmController::setLineAlgorithmConfigDialog(LineDetectionAlgorithmConfigDialog *dialog)
{
    if(lineConfigDialog)
        disconnect(lineConfigChangedConnection);

    lineConfigDialog = dialog;
    lineConfigChangedConnection = connect(lineConfigDialog, &LineDetectionAlgorithmConfigDialog::configChanged,
                                      this, &AlgorithmController::lineDetectionChanged);
    lineDetectionChanged();
}

void AlgorithmController::setObjectAlgorithmConfigDialog(ObjectDetectionAlgorithmConfigDialog *dialog)
{
    if(objectConfigDialog)
        disconnect(objectConfigChangedConnection);

    objectConfigDialog = dialog;
    objectConfigChangedConnection = connect(objectConfigDialog, &ObjectDetectionAlgorithmConfigDialog::configChanged,
                                            this, &AlgorithmController::objectDetectionChanged);

    objectDetectionChanged();
}

void AlgorithmController::setImage(cv::InputArray _image)
{
    cv::Mat image;

    if(_image.channels() == 1)
        image = _image.getMat().clone();
    else
        cv::cvtColor(_image, image, CV_BGR2GRAY);

    queueMutex.lock();
    this->image = image;
    queueMutex.unlock();
    enqueueAlgorithm(true);
}

algorithmworker_result AlgorithmController::getLatestResult()
{
    queueMutex.lock();
    algorithmworker_result returnValue = latestResult;
    queueMutex.unlock();

    return returnValue;
}

void AlgorithmController::lineDetectionChanged()
{
    enqueueAlgorithm(true);
}

void AlgorithmController::objectDetectionChanged()
{
    enqueueAlgorithm(false);
}

void AlgorithmController::enqueueAlgorithm(bool lineConfigChanged)
{
    queueMutex.lock();

    // Enqueue LineDetectionAlgorithm
    if(lineConfigChanged && lineConfigDialog)
    {
        if(queuedAlgorithms.first != 0)
            delete queuedAlgorithms.first;

        queuedAlgorithms.first = lineConfigDialog->createAlgorithm();
    }

    // Enqueue ObjectDetectionAlgorithm
    if(objectConfigDialog)
    {
        if(queuedAlgorithms.second != 0)
            delete queuedAlgorithms.second;
        queuedAlgorithms.second = objectConfigDialog->createAlgorithm();
        queuedAlgorithms.second->setModels(databaseModels);
    }

    queueMutex.unlock();

    // Try to schedule new queue
    scheduleAlgorithm();
}

void AlgorithmController::setDatabaseModels(const std::vector<Model>& models)
{
    queueMutex.lock();
    databaseModels = models;
    queueMutex.unlock();

    objectDetectionChanged();
}

void AlgorithmController::scheduleAlgorithm()
{
    queueMutex.lock();

    // Check conditions for schedule
    bool schedulingPossible = true;

    // Something is running
    if(scheduledAlgorithms.first != 0 || scheduledAlgorithms.second != 0)
        schedulingPossible = false;

    // Queue is empty
    if(queuedAlgorithms.first == 0 && queuedAlgorithms.second == 0)
        schedulingPossible = false;

    // Line detection enqueued, but no image is present
    if(queuedAlgorithms.first != 0 && image.empty())
        schedulingPossible = false;

    // Return if it is not possible to schedule
    if(!schedulingPossible)
    {
        queueMutex.unlock();
        return;
    }

    // Scheduling is possible so schedule
    worker = new AlgorithmWorker(queuedAlgorithms.first, queuedAlgorithms.second,
                                 image.clone(), latestResult.first, this);
    scheduledAlgorithms = queuedAlgorithms;

    // Clean queue
    queuedAlgorithms.first = 0;
    queuedAlgorithms.second = 0;

    // Execute worker
    connect(worker, &AlgorithmWorker::resultReady, this, &AlgorithmController::handleResult);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();

    queueMutex.unlock();

    emit startedCalculation();
}

void AlgorithmController::handleResult()
{
    queueMutex.lock();

    latestResult = worker->getResult();

    // Clean up schedule
    delete scheduledAlgorithms.first;
    scheduledAlgorithms.first = 0;
    delete scheduledAlgorithms.second;
    scheduledAlgorithms.second = 0;

    queueMutex.unlock();

    emit newResultAvailable();
}

} // namespace formseher
