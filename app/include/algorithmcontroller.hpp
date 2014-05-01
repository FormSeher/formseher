#ifndef ALGORITHMCONTROLLER_HPP
#define ALGORITHMCONTROLLER_HPP

#include "algorithm.h"
#include "algorithmconfigdialog.h"

#include <QObject>
#include <QMutex>

class AlgorithmController : public QObject
{
    Q_OBJECT

public:
    AlgorithmController();
    ~AlgorithmController();

    void setAlgorithmConfigDialog(AlgorithmConfigDialog* dialog);

private slots:
    void enqueueAlgorithm();
    void onCalculationFinished();

private:
    QMetaObject::Connection configChangedConnection;
    AlgorithmConfigDialog* configDialog;

    Algorithm* queuedAlgorithm;
    Algorithm* scheduledAlgorithm;

    QMutex queueMutex;
};

#endif // ALGORITHMCONTROLLER_HPP
