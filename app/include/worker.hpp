#ifndef WORKER_HPP
#define WORKER_HPP

#include "algorithmconfigdialog.h"

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

    void setAlgorithmConfigDialog(AlgorithmConfigDialog* dialog);

private slots:
    void enqueueAlgorithm();

private:
    QMetaObject::Connection configChangedConnection;
    AlgorithmConfigDialog* configDialog;
};

#endif // WORKER_HPP
