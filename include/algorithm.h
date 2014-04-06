#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

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
    std::vector<Line*>& getResult();

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
    /**
     * @brief Notify the algorithm that configuration changed.
     *
     * Call this method after an attribute changed which (e.g. via setter). This
     * makes the run() method to notify the change and re-execute calculate() when
     * the algorithm is executed via run().
     */
    void changedConfig();

    /**
     * @brief Set the time the algorithm took to compute its result.
     */
    void setComputationTime(double computationTime);

private:
    bool configChanged;

    std::vector<Line*> result;

    std::string inputFilePath;

    double computationTime;
};

#endif // ALGORITHM_H
