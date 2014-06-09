#ifndef FS_ALGORITHMCONTROLLER_HPP
#define FS_ALGORITHMCONTROLLER_HPP

#include "line.h"
#include "algorithmworker.h"

#include <QObject>
#include <QMutex>
#include <vector>

namespace formseher {

class LineDetectionAlgorithmConfigDialog;
class ObjectDetectionAlgorithmConfigDialog;

class LineDetectionAlgorithm;
class ObjectDetectionAlgorithm;

class Model;

/**
 * @brief Used to form pairs of line and object detection algorithms which are
 * scheduled or put into the queue.
 */
typedef std::pair<LineDetectionAlgorithm*, ObjectDetectionAlgorithm*> algorithm_pair;

/**
 * @brief The AlgorithmController class which controls the execution of AlgorithmWorkers.
 */
class AlgorithmController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief AlgorithmController constructor.
     */
    AlgorithmController();

    /**
     * @brief AlgorithmController destructor.
     */
    ~AlgorithmController();

    /**
     * @brief Set the AlgorithmConfigDialog which is used to create new
     * LineDetectionAlgorithm instances.
     * @param dialog Pointer to an LineDetectionAlgorithmConfigDialog.
     */
    void setLineAlgorithmConfigDialog(LineDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Set the ObjectDetectionAlgorithmConfigDialog which is used to create new
     * ObjectDetectionAlgorithm instances.
     * @param dialog Pointer to the ObjectDetectionConfigDialog.
     */
    void setObjectAlgorithmConfigDialog(ObjectDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Set the image on which the AlgorithmWorkers should operate.
     * @param image The image.
     */
    void setImage(cv::InputArray image);

    /**
     * @brief Get the result of the latest executed AlgorithmWorker.
     * @return The result @see Algorithm.calculate()
     */
    algorithmworker_result getLatestResult();

    /**
     * @brief Set models which are passed to ObjectDetectionAlgorithms.
     * @param models Vector of Models.
     */
    void setDatabaseModels(const std::vector<Model>& models);

signals:
    /**
     * @brief Signaml emitted when an AlgorithmWorker finished and a new result is available.
     */
    void newResultAvailable();

public slots:
    /**
     * @brief Called if line detection config changed.
     **/
    void lineDetectionChanged();

    /**
     * @brief Called if object detection config changed.
     */
    void objectDetectionChanged();

private slots:
    /**
     * @brief Schedule the waiting algorithm.
     */
    void scheduleAlgorithm();

    /**
     * @brief Called after a AlgorithmWorker published its result.
     */
    void handleResult();

private:
    /**
     * @brief Enqueue a new Algorithm.
     */
    void enqueueAlgorithm(bool lineConfigChanged);

    /**
     * @brief Used to manage connections to LineDetectionAlgorithmConfigDialog instances.
     */
    QMetaObject::Connection lineConfigChangedConnection;

    /**
     * @brief The LineDetectionAlgorithmConfigDialog currently used to create LineAlgorithm instances.
     */
    LineDetectionAlgorithmConfigDialog* lineConfigDialog;

    /**
     * @brief Used to manage connections to ObjectDetectionConfigDialog instances.
     */
    QMetaObject::Connection objectConfigChangedConnection;

    /**
     * @brief The ObjectDetectionAlgorithmConfigDialog currently used to create ObjectAlgorithm instances.
     */
    ObjectDetectionAlgorithmConfigDialog* objectConfigDialog;

    /**
     * @brief The currently used image
     */
    cv::Mat image;

    /**
     * @brief The next algorithms waiting for execution.
     */
    algorithm_pair queuedAlgorithms;

    /**
     * @brief The currently running algorithms.
     */
    algorithm_pair scheduledAlgorithms;

    /**
     * @brief The currently running AlgorithmWorker.
     */
    AlgorithmWorker* worker;

    /**
     * @brief Mutex used for threadsave queue access.
     */
    QMutex queueMutex;

    /**
     * @brief The latest result returned by one of the AlgorithmWorkers.
     */
    algorithmworker_result latestResult;

    /**
     * @brief Models from a database which are passed to ObjectDetectionAlgorithms.
     */
    std::vector<Model> databaseModels;
};

} // namespace formseher

#endif // FS_ALGORITHMCONTROLLER_HPP
