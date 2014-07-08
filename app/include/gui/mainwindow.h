#ifndef FS_MAINWINDOW_H
#define FS_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <map>
#include <string>

#include "gui/linedetection/linedetectionalgorithmconfigdialog.h"
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
    /**
     * @brief MainWindow standard constructor.
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * MainWindow destructor.
     */
    ~MainWindow();

    /**
     * @brief Registers a LineDetectionAlgorithmConfigDialog.
     * @param slot Specify if dialog is assigned to left (0) or right (1) AlgorithmControlWidget.
     * @param id Id of the config dialog.
     * @param dialog Pointer to dialog instance.
     * @return Return if registration was successful.
     */
    bool registerLineAlgorithmConfigDialog(int slot, std::string id, LineDetectionAlgorithmConfigDialog* dialog);

    /**
     * @brief Registers a ObjectDetectionAlgorithmConfigDialog.
     * @param slot Specify if dialog is assigned to left (0) or right (1) AlgorithmControlWidget.
     * @param id Id of the config dialog.
     * @param dialog Pointer to dialog instance.
     * @return Return if registration was successful.
     */
    bool registerObjectAlgorithmConfigDialog(int slot, std::string id, ObjectDetectionAlgorithmConfigDialog* dialog);

private:
    Ui::MainWindow *ui;

    AlgorithmControlWidget* algorithmControlWidgets[2];
};

} // namespace formseher

#endif // FS_MAINWINDOW_H
