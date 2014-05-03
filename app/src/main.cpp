#include <mainwindow.h>
#include <QApplication>

#include "algorithmconfigdialog.h"
#include "edl/edlconfigdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EDLConfigDialog edlDialog1;
    EDLConfigDialog edlDialog2;

    MainWindow w;

    w.registerAlgorithmConfigDialog(1, "EDL", static_cast<AlgorithmConfigDialog*>(&edlDialog1));
    w.registerAlgorithmConfigDialog(2, "EDL", static_cast<AlgorithmConfigDialog*>(&edlDialog2));

    w.show();

    return a.exec();
}
