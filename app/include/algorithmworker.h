#ifndef ALGORITHMWORKER_H
#define ALGORITHMWORKER_H

#include "algorithm.h"
#include "line.h"

#include <QThread>
#include <opencv2/core/core.hpp>
#include <vector>

class AlgorithmWorker : public QThread
{
    Q_OBJECT
public:
    explicit AlgorithmWorker(Algorithm* algorithm, cv::InputArray image, QObject *parent = 0);

    ~AlgorithmWorker();

    void run() Q_DECL_OVERRIDE;

signals:
    void resultReady(std::vector<Line> result);

public slots:

private:
    Algorithm* algorithm;
    cv::Mat image;
};

#endif // ALGORITHMWORKER_H
