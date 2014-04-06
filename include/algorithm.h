#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>

class Line;

class Algorithm
{
public:
    Algorithm();

    virtual void calculate() = 0;

    bool startThreaded();
    void run();

    std::vector<Line*>& getResult();

protected:
    void changedConfig();

private:
    bool configChanged;

    std::vector<Line*> result;
};

#endif // ALGORITHM_H
