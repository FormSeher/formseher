#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <string>

namespace Ui {
class MainWindow;
}

class AlgorithmConfigDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool addAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog* dialog);

private:
    Ui::MainWindow *ui;

    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
};

#endif // MAINWINDOW_H
