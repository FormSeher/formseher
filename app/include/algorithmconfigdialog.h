#ifndef ALGORITHMCONFIGDIALOG_H
#define ALGORITHMCONFIGDIALOG_H

#include <QDialog>

class Algorithm;

/**
 * @brief The AlgorithmConfigDialog class used to configure an algorithm.
 *
 * Each algorithm is shipped with an custom AlgorithmConfigDialog. This dialog
 * is responsible for the configuratoin of any parameters that can be tweaked.
 */
class AlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Standard ctor
     * @param parent
     */
    explicit AlgorithmConfigDialog(QWidget *parent = 0);

    /**
     * @brief Return a pointer to the algorithm.
     * @return Pointer to the algorithm.
     */
    virtual Algorithm* getAlgorithm() = 0;

signals:

public slots:

};

#endif // ALGORITHMCONFIGDIALOG_H
