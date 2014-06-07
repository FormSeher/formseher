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
     * @brief Set the AlgorithmConfigDialog which is used to create new Algorithm instances.
     * @param dialog Pointer to an AlgorithmConfigDialog.
     */
    void setAlgorithmConfigDialog(LineDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Set the image on which the AlgorithmWorkers should operate.
     * @param image The image.
     */
    void setImage(cv::InputArray image);

    /**
     * @brief Get the result of the latest executed AlgorithmWorker.
     * @return The result @see Algorithm.calculate()
     */
    std::vector<Line> getLatestResult();

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
     * @brief Used to manage connections to AlgorithmConfigDialog instances.
     */
    QMetaObject::Connection configChangedConnection;

    /**
     * @brief The LineDetectionAlgorithmConfigDialog currently used to create LineAlgorithm instances.
     */
    LineDetectionAlgorithmConfigDialog* lineConfigDialog;

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
    std::vector<Line> latestResult;
};

} // namespace formseher

#endif // FS_ALGORITHMCONTROLLER_HPP
