#ifndef FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H
#define FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H

#include <QDialog>

namespace formseher
{

class LineDetectionAlgorithm;

/**
 * @brief The AlgorithmConfigDialog class used to configure an algorithm.
 *
 * Each algorithm is shipped with an custom AlgorithmConfigDialog. This dialog
 * works as a factory which creates new Algorithm instances.
 */
class LineDetectionAlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Standard ctor
     * @param parent
     */
    explicit LineDetectionAlgorithmConfigDialog(QWidget *parent = 0);

    /**
     * @brief Create a new Algorithm instance.
     *
     * This is a factory method which creates a new Algorithm instance
     * with the currently configured parameters.
     *
     * @return Pointer to the new Algorithm.
     */
    virtual LineDetectionAlgorithm* createAlgorithm() = 0;

signals:
    /**
     * Emit this signal if the configuration was changed.
     */
    void configChanged();

public slots:

};

} // namespace formseher

#endif // FS_LINEDETECTIONALGORITHMCONFIGDIALOG_H
