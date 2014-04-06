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

    /**
     * @brief Adds an AlgorithmConfigDialog to the MainWindow.
     * @param id Id which can be used to identify the algorithm inside the MainWindow.
     * @param dialog Pointer to an AlgorithmConfigDialog.
     * @return True if algorithm was added, false if there is already an algorithm
     * registered with the given id.
     */
    bool addAlgorithmConfigDialog(std::string id, AlgorithmConfigDialog* dialog);

private:
    Ui::MainWindow *ui;

    /**
     * @brief Holds ID -> AlgorithmConfigDialog-Pointer pairs.
     */
    std::map<std::string, AlgorithmConfigDialog*> algorithmConfigDialogs;
};

#endif // MAINWINDOW_H
