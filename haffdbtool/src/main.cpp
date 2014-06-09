#include "hdbmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HDBMainWindow w;
    w.show();
    w.resize(w.maximumSize());
    return a.exec();
}
