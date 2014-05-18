#include <gui/mainwindow.h>
#include <QApplication>

#include "gui/algorithmconfigdialog.h"
#include "gui/edl/edlconfigdialog.h"
#include "gui/hough/houghconfigdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    formseher::EDLConfigDialog edlDialog1;
    formseher::EDLConfigDialog edlDialog2;

    formseher::HoughConfigDialog houghDialog1;
    formseher::HoughConfigDialog houghDialog2;

    formseher::MainWindow w;


    w.registerAlgorithmConfigDialog(1, "EDL", static_cast<formseher::AlgorithmConfigDialog*>(&edlDialog1));
    w.registerAlgorithmConfigDialog(2, "EDL", static_cast<formseher::AlgorithmConfigDialog*>(&edlDialog2));
    w.registerAlgorithmConfigDialog(1, "Hough", static_cast<formseher::AlgorithmConfigDialog*>(&houghDialog1));
    w.registerAlgorithmConfigDialog(2, "Hough", static_cast<formseher::AlgorithmConfigDialog*>(&houghDialog2));

    w.show();

    return a.exec();
}
