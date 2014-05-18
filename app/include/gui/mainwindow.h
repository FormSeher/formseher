#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <string>

#include "algorithmconfigdialog.h"
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

    bool registerAlgorithmConfigDialog(int slot, std::string id, AlgorithmConfigDialog* dialog);

private:
    Ui::MainWindow *ui;

    AlgorithmControlWidget* algorithmControlWidgets[2];
};

} // namespace formseher

#endif // MAINWINDOW_H
