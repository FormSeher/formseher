#include "hdbmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HDBMainWindow w;
    w.resize(w.maximumSize());
    w.setWindowTitle(QString("Haff Database Tool"));
    w.show();

    return a.exec();
}
