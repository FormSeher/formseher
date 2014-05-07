#ifndef ALGORITHMWORKER_H
#define ALGORITHMWORKER_H

#include "linedetection/algorithm.h"
#include "line.h"

#include <QThread>
#include <opencv2/core/core.hpp>
#include <vector>

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
    explicit AlgorithmWorker(Algorithm* algorithm, cv::InputArray image, QObject *parent = 0);

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
    std::vector<Line> getResult();

signals:
    /**
     * @brief Signal that is emitted when the result of the algorithm becomes available.
     */
    void resultReady();

private:
    Algorithm* algorithm;
    cv::Mat image;
    std::vector<Line> result;
};

#endif // ALGORITHMWORKER_H
