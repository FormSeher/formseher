#ifndef STUBCONFIGDIALOG_H
#define STUBCONFIGDIALOG_H

#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

namespace formseher
{

class StubConfigDialog : public ObjectDetectionAlgorithmConfigDialog
{
public:
    StubConfigDialog();

    ObjectDetectionAlgorithm* createAlgorithm();
};

} // namespace formseher

#endif // STUBCONFIGDIALOG_H
