#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

class Line;

class Algorithm
{
public:
    Algorithm();

    virtual void calculate() = 0;

    bool startThreaded();
    void run();

    std::vector<Line*>& getResult();

    void setInput(std::string filePath);

protected:
    void changedConfig();

private:
    bool configChanged;

    std::vector<Line*> result;

    std::string inputFilePath;
};

#endif // ALGORITHM_H
