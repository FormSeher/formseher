#ifndef OBJECTDETECTIONALGORITHMTEAMBDIALOG_CPP
#define OBJECTDETECTIONALGORITHMTEAMBDIALOG_CPP

#include "gui/objectdetection/teamb/objectdetectionalgorithmteambdialog.h"
#include "objectdetection/teamb/objectdetectionalgorithmteamb.h"

namespace formseher
{

ObjectDetectionAlgorithmTeamBDialog::ObjectDetectionAlgorithmTeamBDialog()
{
}

ObjectDetectionAlgorithm *ObjectDetectionAlgorithmTeamBDialog::createAlgorithm()
{
    return new ObjectDetectionAlgorithmTeamB();
}

} // namespace formseher

#endif // OBJECTDETECTIONALGORITHMTEAMBDIALOG_CPP
