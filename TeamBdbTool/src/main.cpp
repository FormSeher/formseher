#include "teambdbtool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TeamBdbTool w;
    w.show();

    return a.exec();
}
