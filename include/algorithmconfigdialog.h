#ifndef ALGORITHMCONFIGDIALOG_H
#define ALGORITHMCONFIGDIALOG_H

#include <QDialog>

class Algorithm;

class AlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AlgorithmConfigDialog(QWidget *parent = 0);

    virtual Algorithm* getAlgorithm() = 0;

signals:

public slots:

};

#endif // ALGORITHMCONFIGDIALOG_H
