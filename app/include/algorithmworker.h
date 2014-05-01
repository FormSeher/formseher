#ifndef ALGORITHMWORKER_H
#define ALGORITHMWORKER_H

#include <QThread>

class AlgorithmWorker : public QThread
{
    Q_OBJECT
public:
    explicit AlgorithmWorker(QObject *parent = 0);

signals:

public slots:

};

#endif // ALGORITHMWORKER_H
