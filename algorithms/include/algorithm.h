#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <opencv2/core/core.hpp>

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
    virtual std::vector<Line> calculate(cv::InputArray image) = 0;
};

#endif // ALGORITHM_H
