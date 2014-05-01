#ifndef ALGORITHMCONTROLLER_HPP
#define ALGORITHMCONTROLLER_HPP

#include "algorithm.h"
#include "algorithmconfigdialog.h"
#include "line.h"
#include "algorithmworker.h"

#include <QObject>
#include <QMutex>
#include <vector>

class AlgorithmController : public QObject
{
    Q_OBJECT

public:
    AlgorithmController();
    ~AlgorithmController();

    void setAlgorithmConfigDialog(AlgorithmConfigDialog* dialog);
    void setImage(cv::InputArray image);

    std::vector<Line> getLatestResult();

signals:
    void newResultAvailable();

private slots:
    void enqueueAlgorithm();
    void scheduleAlgorithm();
    void handleResult();

private:
    QMetaObject::Connection configChangedConnection;
    AlgorithmConfigDialog* configDialog;

    cv::Mat image;

    Algorithm* queuedAlgorithm;
    Algorithm* scheduledAlgorithm;
    AlgorithmWorker* worker;

    QMutex queueMutex;

    std::vector<Line> latestResult;
};

#endif // ALGORITHMCONTROLLER_HPP
