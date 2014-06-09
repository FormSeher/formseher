#ifndef FS_MAINWINDOW_H
#define FS_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <string>

#include "gui/linedetectionalgorithmconfigdialog.h"
#include "threading/algorithmcontroller.hpp"
#include "algorithmcontrolwidget.h"

namespace Ui {
class MainWindow;
}

namespace formseher
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool registerLineAlgorithmConfigDialog(int slot, std::string id, LineDetectionAlgorithmConfigDialog* dialog);
    bool registerObjectAlgorithmConfigDialog(int slot, std::string id, ObjectDetectionAlgorithmConfigDialog* dialog);

private slots:
    void updateStatusBar(QString statusString);

private:
    Ui::MainWindow *ui;

    AlgorithmControlWidget* algorithmControlWidgets[2];
};

} // namespace formseher

#endif // FS_MAINWINDOW_H
