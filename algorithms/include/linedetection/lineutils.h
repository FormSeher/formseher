#ifndef LINEUTILS_H
#define LINEUTILS_H

#include "line.h"

namespace formseher {

class LineUtils
{
public:
    LineUtils();

    /**
     * @brief combineLines Combines lines in the given vector that represent logically the same line.
     * @param lineList Lines from linedetection algorithm.
     * @return Vector that contains just the combined lines.
     */
    static void combineLines(std::vector<Line>& lineList);
};

} // namesspace formseher

#endif // LINEUTILS_H
