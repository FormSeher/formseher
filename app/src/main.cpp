#include <mainwindow.h>
#include <QApplication>

#include "algorithmconfigdialog.h"
#include "edl/edlconfigdialog.h"
#include "hough/houghconfigdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EDLConfigDialog edlDialog1;
    EDLConfigDialog edlDialog2;

    HoughConfigDialog houghDialog1;
    HoughConfigDialog houghDialog2;

    MainWindow w;


    w.registerAlgorithmConfigDialog(1, "EDL", static_cast<AlgorithmConfigDialog*>(&edlDialog1));
    w.registerAlgorithmConfigDialog(2, "EDL", static_cast<AlgorithmConfigDialog*>(&edlDialog2));
    w.registerAlgorithmConfigDialog(1, "Hough", static_cast<AlgorithmConfigDialog*>(&houghDialog1));
    w.registerAlgorithmConfigDialog(2, "Hough", static_cast<AlgorithmConfigDialog*>(&houghDialog2));

    w.show();

    return a.exec();
}
