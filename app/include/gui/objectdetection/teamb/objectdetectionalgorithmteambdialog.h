#ifndef OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
#define OBJECTDETECTIONALGORITHMTEAMBDIALOG_H

#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

namespace formseher
{

class ObjectDetectionAlgorithmTeamBDialog : public ObjectDetectionAlgorithmConfigDialog
{
public:
    ObjectDetectionAlgorithmTeamBDialog();

    ObjectDetectionAlgorithm* createAlgorithm();
};

} // namespace formseher

#endif // OBJECTDETECTIONALGORITHMTEAMBDIALOG_H
