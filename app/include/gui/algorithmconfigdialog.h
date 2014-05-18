#ifndef ALGORITHMCONFIGDIALOG_H
#define ALGORITHMCONFIGDIALOG_H

#include <QDialog>

namespace formseher
{

class Algorithm;

/**
 * @brief The AlgorithmConfigDialog class used to configure an algorithm.
 *
 * Each algorithm is shipped with an custom AlgorithmConfigDialog. This dialog
 * works as a factory which creates new Algorithm instances.
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
     * @brief Create a new Algorithm instance.
     *
     * This is a factory method which creates a new Algorithm instance
     * with the currently configured parameters.
     *
     * @return Pointer to the new Algorithm.
     */
    virtual Algorithm* createAlgorithm() = 0;

signals:
    /**
     * Emit this signal if the configuration was changed.
     */
    void configChanged();

public slots:

};

} // namespace formseher

#endif // ALGORITHMCONFIGDIALOG_H
