/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

#include "threading/algorithmworker.h"

#include "linedetection/linedetectionalgorithm.h"
#include "linedetection/lineutils.h"
#include "objectdetection/objectdetectionalgorithm.h"

#include "line.h"
#include "objectdetection/object.h"

namespace formseher
{

AlgorithmWorker::AlgorithmWorker(LineDetectionAlgorithm* lineAlgorithm, ObjectDetectionAlgorithm *objectAlgorithm, cv::InputArray image, std::vector<Line> presetLines, QObject *parent)
    : QThread(parent),
      lineAlgorithm(lineAlgorithm),
      objectAlgorithm(objectAlgorithm)
{
    this->image = image.getMat();

    if(!presetLines.empty())
        this->result.first = presetLines;
}

AlgorithmWorker::~AlgorithmWorker()
{
}

void AlgorithmWorker::run()
{
    if(lineAlgorithm)
    {
        result.first = lineAlgorithm->calculate(image);
        LineUtils::combineLines(result.first);
    }

    if(objectAlgorithm)
        result.second = objectAlgorithm->calculate(result.first);
    emit resultReady();
}

algorithmworker_result AlgorithmWorker::getResult()
{
    return result;
}

} // namespace formseher
