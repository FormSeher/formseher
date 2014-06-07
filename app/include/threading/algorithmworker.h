#ifndef FS_ALGORITHMWORKER_H
#define FS_ALGORITHMWORKER_H

#include <QThread>
#include <opencv2/core/core.hpp>
#include <vector>

namespace formseher
{

class LineDetectionAlgorithm;
class ObjectDetectionAlgorithm;
class Line;
class Object;

/**
 * @brief Used to return result of AlgorithmWorker easier.
 */
typedef std::pair<std::vector<Line>, std::vector<Object>> algorithmworker_result;

/**
 * @brief The AlgorithmWorker class
 *
 * The AlgorithmWorker encapsulates an Algorithm in an QThread.
 */
class AlgorithmWorker : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief AlgorithmWorker constructor.
     * @param algorithm The Algorithm to execute.
     * @param image The image on which the Algorithm is executed.
     * @param parent The parent.
     */
    explicit AlgorithmWorker(LineDetectionAlgorithm* lineAlgorithm,
                             ObjectDetectionAlgorithm* objectAlgorithm,
                             cv::InputArray image,
                             std::vector<Line> presetLines,
                             QObject *parent = 0);

    /**
     * @brief Destructor
     * Deletes itself and the Algorithm instance.
     */
    ~AlgorithmWorker();

    /**
     * @brief Run the Worker in a separate thread.
     */
    void run() Q_DECL_OVERRIDE;

    /**
     * @brief Get the result of the Algorithm.
     * @return The result of the Algorithm @see Algorithm.calculate()
     */
    algorithmworker_result getResult();

signals:
    /**
     * @brief Signal that is emitted when the result of the algorithm becomes available.
     */
    void resultReady();

private:
    LineDetectionAlgorithm* lineAlgorithm;
    ObjectDetectionAlgorithm* objectAlgorithm;
    cv::Mat image;
    algorithmworker_result result;
};

} // namespace formseher

#endif // FS_ALGORITHMWORKER_H
