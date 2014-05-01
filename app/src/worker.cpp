#include "worker.hpp"

#include <iostream>

Worker::Worker()
    : configDialog(0)
{}

Worker::~Worker()
{}

void Worker::setAlgorithmConfigDialog(AlgorithmConfigDialog *dialog)
{
    if(configDialog)
        disconnect(configChangedConnection);

    configDialog = dialog;
    configChangedConnection = connect(configDialog, &AlgorithmConfigDialog::configChanged,
                                               this, &Worker::enqueueAlgorithm);
}

void Worker::enqueueAlgorithm()
{
    std::cout << "enqueue Algorithm\n";
}
