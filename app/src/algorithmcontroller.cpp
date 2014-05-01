#include "algorithmcontroller.hpp"

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

void AlgorithmController::onCalculationFinished()
{
    queueMutex.lock();
    delete scheduledAlgorithm;
    scheduledAlgorithm = 0;
    queueMutex.unlock();
}
