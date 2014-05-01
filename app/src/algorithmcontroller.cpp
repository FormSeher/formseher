#include "algorithmcontroller.hpp"

#include "algorithmworker.h"

#include <iostream>

AlgorithmController::AlgorithmController()
    : configDialog(0),
      queuedAlgorithm(0),
      scheduledAlgorithm(0)
{}

AlgorithmController::~AlgorithmController()
{
    if(queuedAlgorithm)
        delete queuedAlgorithm;
}

void AlgorithmController::setAlgorithmConfigDialog(AlgorithmConfigDialog *dialog)
{
    if(configDialog)
        disconnect(configChangedConnection);

    configDialog = dialog;
    configChangedConnection = connect(configDialog, &AlgorithmConfigDialog::configChanged,
                                      this, &AlgorithmController::enqueueAlgorithm);
}

void AlgorithmController::setImage(cv::InputArray image)
{
    queueMutex.lock();
    this->image = image.getMat();
    queueMutex.unlock();
}

void AlgorithmController::enqueueAlgorithm()
{
    Algorithm* newAlgorithm = configDialog->createAlgorithm();

    queueMutex.lock();
    if(queuedAlgorithm != 0)
        delete queuedAlgorithm;
    queuedAlgorithm = newAlgorithm;
    queueMutex.unlock();

    std::cout << "enqueued algorithm...." << std::endl;

    //scheduleAlgorithm()
}

void AlgorithmController::scheduleAlgorithm()
{
    queueMutex.lock();

    if(scheduledAlgorithm != 0 || queuedAlgorithm == 0)
    {
        queueMutex.unlock();
        return;
    }

    AlgorithmWorker* worker = new AlgorithmWorker(queuedAlgorithm, image, this);
    connect(worker, &AlgorithmWorker::resultReady, this, &AlgorithmController::handleResult);
    connect(worker, &AlgorithmWorker::finished, this, &AlgorithmController::scheduleAlgorithm);
    connect(worker, &AlgorithmWorker::finished, worker, &QObject::deleteLater);
    worker->start();

    queueMutex.unlock();
}

void AlgorithmController::handleResult(std::vector<Line> result)
{
    queueMutex.lock();
    scheduledAlgorithm = 0;
    emit newResultAvailable(result);
    queueMutex.unlock();
}
