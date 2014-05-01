#ifndef ALGORITHMCONTROLLER_HPP
#define ALGORITHMCONTROLLER_HPP

#include "algorithm.h"
#include "algorithmconfigdialog.h"
#include "line.h"

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

signals:
    void newResultAvailable(std::vector<Line> result);

private slots:
    void enqueueAlgorithm();
    void scheduleAlgorithm();
    void handleResult(std::vector<Line> result);

private:
    QMetaObject::Connection configChangedConnection;
    AlgorithmConfigDialog* configDialog;

    cv::Mat image;

    Algorithm* queuedAlgorithm;
    Algorithm* scheduledAlgorithm;

    QMutex queueMutex;
};

#endif // ALGORITHMCONTROLLER_HPP
