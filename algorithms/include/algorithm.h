#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class Line;

/**
 * @brief The abstract Algorithm class used to implement line detection algorithms.
 *
 * Derive from this class to create a custom line detection algorithm.
 */
class Algorithm
{
public:
    /**
     * @brief Standard ctor
     */
    Algorithm();

    /**
     * @brief Standard dtor
     */
    virtual ~Algorithm();

    /**
     * @brief Run the algorithm once.
     *
     * This method is called to execute the algorithm one time. You have to implement
     * it when you create a custom line detection algorithm. This method should update
     * the result vector.
     */
    virtual void calculate() = 0;

    /**
     * @brief Start the algorithm in a new thread.
     *
     * When invoking startThreaded, a new thread is created which runs the run() method.
     *
     * @return True when thread creation was successful, false otherwise.
     */
    bool startThreaded();

    /**
     * @brief Stops the thread.
     * Stop the thread and wait until it is finished. Destroys the thread afterwards.
     */
    void stopThreaded();

    /**
     * @brief Runs the algorithm in a loop.
     *
     * Runs the algorithm in a loop and executes calculate() in each iteration. Used to
     * run the algorithm in a thread.
     * @see startThreaded
     */
    void run();

    /**
     * @brief Get the result of the last calculate() execution.
     * @return Result of last calculate() execution.
     */
    std::vector<Line*>* getResult();

    /**
     * @brief Get the time the algorithm took to compute its result.
     * @return The elapsed time.
     */
    double getCoputationTime();

    /**
     * @brief Set the path to a file which is processed by calculate().
     * @param filePath Filepath of an image file.
     */
    void setInput(std::string filePath);

protected:
    void setConfigChanged(bool configChanged);

    /**
     * @brief Set the outcome and computation time of the algorithm.
     * @param result Vector which holds the Lines found by the algorithm
     * @param computationTime The time the alrogithm spend to compute the result in seconds.
     */
    void setResult(std::vector<Line*>* result, double computationTime);

    std::mutex configChangedMutex;
    std::mutex configVariablesMutex;
    std::mutex resultMutex;

    std::condition_variable configChangedCondition;
    std::mutex configConditionMutex;

private:
    bool configChanged;

    std::vector<Line*>* result;

    std::string inputFilePath;

    double computationTime;

    std::thread* thread;
    bool stopThread;
};

#endif // ALGORITHM_H
