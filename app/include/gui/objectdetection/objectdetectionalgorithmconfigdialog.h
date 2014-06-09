#ifndef FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H
#define FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H

#include <QDialog>

namespace formseher
{

class ObjectDetectionAlgorithm;

/**
 * @brief The ObjectDetectionAlgorithmConfigDialog class used to configure an ObjectDetectionAlgorithm.
 *
 * Each ObjectDetectionAlgorithm is shipped with an custom ObjectDetectionAlgorithmConfigDialog. This dialog
 * works as a factory which creates new ObjectDetectionAlgorithm instances.
 */
class ObjectDetectionAlgorithmConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Standard ctor
     * @param parent
     */
    explicit ObjectDetectionAlgorithmConfigDialog(QWidget *parent = 0);

    /**
     * @brief Create a new ObjectDetectionAlgorithm instance.
     *
     * This is a factory method which creates a new ObjectDetectionAlgorithm instance
     * with the currently configured parameters.
     *
     * @return Pointer to the new ObjectDetectionAlgorithm.
     */
    virtual ObjectDetectionAlgorithm* createAlgorithm() = 0;

signals:
    /**
     * Emit this signal if the configuration was changed.
     */
    void configChanged();
};

} // namespace formseher

#endif // FS_OBJECTDETECTIONALGORITHMCONFIGWINDOW_H
