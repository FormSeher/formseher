#include "threading/algorithmcontroller.hpp"

#include "gui/linedetectionalgorithmconfigdialog.h"
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

void AlgorithmController::setAlgorithmConfigDialog(LineDetectionAlgorithmConfigDialog *dialog)
{
    if(lineConfigDialog)
        disconnect(configChangedConnection);

    lineConfigDialog = dialog;
    configChangedConnection = connect(lineConfigDialog, &LineDetectionAlgorithmConfigDialog::configChanged,
                                      this, &AlgorithmController::enqueueAlgorithm);
}

void AlgorithmController::setImage(cv::InputArray image)
{
    queueMutex.lock();
    this->image = image.getMat();
    queueMutex.unlock();
}

std::vector<Line> AlgorithmController::getLatestResult()
{
    return latestResult;
}

void AlgorithmController::enqueueAlgorithm()
{
    if(!lineConfigDialog)
        return;

    LineDetectionAlgorithm* newLineAlgorithm = lineConfigDialog->createAlgorithm();
    ObjectDetectionAlgorithm* newObjectAlgorithm = objectConfigDialog->createAlgorithm();

    queueMutex.lock();

    // Clean queue if necessary
    if(queuedAlgorithms.first != 0)
        delete queuedAlgorithms.first;
    if(queuedAlgorithms.second != 0)
        delete queuedAlgorithms.second;

    // Enqueue new algorithms
    queuedAlgorithms.first = newLineAlgorithm;
    queuedAlgorithms.second = newObjectAlgorithm;

    queueMutex.unlock();

    // Try to schedule new queue
    scheduleAlgorithm();
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
    if(queuedAlgorithms.first == 0 || queuedAlgorithms.second == 0)
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
    worker = new AlgorithmWorker(queuedAlgorithms.first, image.clone(), this);
    scheduledAlgorithms = queuedAlgorithms;

    // Clean queue
    queuedAlgorithms.first = 0;
    queuedAlgorithms.second = 0;

    // Execute worker
    connect(worker, &AlgorithmWorker::resultReady, this, &AlgorithmController::handleResult);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();

    queueMutex.unlock();
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
    emit newResultAvailable();

    queueMutex.unlock();
}

} // namespace formseher
