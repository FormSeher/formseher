#include <gui/mainwindow.h>
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "gui/edl/edlconfigdialog.h"
#include "gui/hough/houghconfigdialog.h"

#include "gui/objectdetection/stub/stubconfigdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    formseher::EDLConfigDialog edlDialog1;
    formseher::EDLConfigDialog edlDialog2;

    formseher::HoughConfigDialog houghDialog1;
    formseher::HoughConfigDialog houghDialog2;

    formseher::StubConfigDialog stubDialog1;
    formseher::StubConfigDialog stubDialog2;

    formseher::MainWindow w;

    w.registerLineAlgorithmConfigDialog(1, "EDL", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edlDialog1));
    w.registerLineAlgorithmConfigDialog(2, "EDL", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&edlDialog2));
    w.registerLineAlgorithmConfigDialog(1, "Hough", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&houghDialog1));
    w.registerLineAlgorithmConfigDialog(2, "Hough", static_cast<formseher::LineDetectionAlgorithmConfigDialog*>(&houghDialog2));

    w.registerObjectAlgorithmConfigDialog(1, "Stub", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&stubDialog1));
    w.registerObjectAlgorithmConfigDialog(2, "Stub", static_cast<formseher::ObjectDetectionAlgorithmConfigDialog*>(&stubDialog2));

    w.show();

    return a.exec();
}
