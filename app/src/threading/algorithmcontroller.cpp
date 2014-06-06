#include "threading/algorithmcontroller.hpp"

#include "gui/linedetectionalgorithmconfigdialog.h"
#include "threading/algorithmworker.h"

namespace formseher
{

AlgorithmController::AlgorithmController()
    : lineConfigDialog(0),
      queuedAlgorithm(0),
      scheduledAlgorithm(0)
{}

AlgorithmController::~AlgorithmController()
{
    if(queuedAlgorithm)
        delete queuedAlgorithm;
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

    LineDetectionAlgorithm* newAlgorithm = lineConfigDialog->createAlgorithm();

    queueMutex.lock();
    if(queuedAlgorithm != 0)
        delete queuedAlgorithm;
    queuedAlgorithm = newAlgorithm;
    queueMutex.unlock();

    scheduleAlgorithm();
}

void AlgorithmController::scheduleAlgorithm()
{
    queueMutex.lock();

    if(scheduledAlgorithm != 0 || queuedAlgorithm == 0 || image.empty())
    {
        queueMutex.unlock();
        return;
    }

    worker = new AlgorithmWorker(queuedAlgorithm, image.clone(), this);
    scheduledAlgorithm = queuedAlgorithm;
    queuedAlgorithm = 0;
    connect(worker, &AlgorithmWorker::resultReady, this, &AlgorithmController::handleResult);
    connect(worker, &QThread::finished, worker, &QObject::deleteLater);
    worker->start();

    queueMutex.unlock();
}

void AlgorithmController::handleResult()
{
    queueMutex.lock();

    latestResult = worker->getResult();

    scheduledAlgorithm = 0;
    emit newResultAvailable();

    queueMutex.unlock();
}

} // namespace formseher
