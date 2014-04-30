#include <mainwindow.h>
#include <QApplication>

#include "algorithmconfigdialog.h"
#include "edl/edlconfigdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EDLConfigDialog edlDialog;

    MainWindow w;
    w.registerAlgorithmConfigDialog("EDL", static_cast<AlgorithmConfigDialog*>(&edlDialog));
    w.show();

    return a.exec();
}
