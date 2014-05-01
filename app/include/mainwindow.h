#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <string>

#include "algorithmconfigdialog.h"
#include "algorithmcontroller.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool registerAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog* dialog);

private slots:
    void on_openpicture1_clicked();

    void on_openpicture2_clicked();

    void on_save1_clicked();

    void on_save2_clicked();

    void on_lineEdit1_returnPressed();

    void on_lineEdit2_returnPressed();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(const QString &algorithmId);

    void on_pushButton_clicked();

    void on_worker1_newResultAvailable(std::vector<Line> result);

private:
    Ui::MainWindow *ui;

    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
    AlgorithmConfigDialog* selectedAlgorithmDialog;
    AlgorithmController controller1;
};

#endif // MAINWINDOW_H
