#include "gui/objectdetection/stub/stubconfigdialog.h"

#include "objectdetection/stub/stub.h"

namespace formseher
{

StubConfigDialog::StubConfigDialog()
{
}

ObjectDetectionAlgorithm *StubConfigDialog::createAlgorithm()
{
    return new Stub();
}

} // namespace formseher
