#ifndef HDBMAINWINDOW_H
#define HDBMAINWINDOW_H

// Database tool
#include "learningobject.h"
#include "settings.h"

// Qt
#include <QMainWindow>

namespace Ui {
class HDBMainWindow;
}

/**
 * @brief The HDBMainWindow class is a Qt UI class which
 * holds all other widgets and dialogs. It also connects the
 * slots of these widgets and dialogs and holds the mainwindow
 * action button logic.
 */
class HDBMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief HDBMainWindow standard constructor.
     * @param parent Parent widget.
     */
    explicit HDBMainWindow(QWidget *parent = 0);
    ~HDBMainWindow();

signals:
    /**
     * @brief signal_statusChange Signal that gets emmited if the statusbar content should be changed.
     */
    void signal_statusChange(QString);

    /**
     * @brief signal_windowResize Signal that gets emmited if the window gets resized.
     */
    void signal_windowResize();


private slots:
    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to open a image.
     */
    void slot_actionOpenImage_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to create a database.
     */
    void slot_actionCreateDatabase_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to open a database.
     */
    void slot_actionOpenDatabase_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to save a object.
     */
    void slot_actionSaveObject_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to open the settings.
     */
    void slot_actionSettings_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to open the drawing window.
     */
    void slot_actionDraw_clicked();

    /**
     * @brief slot_actionOpenImage_clicked Slot that gets connected to the toolbar's action button to open the AddLineDialog.
     */
    void slot_actionAddLine_clicked();

private:
    Ui::HDBMainWindow* ui;

    /**
     * @brief learningObject Pointer to the current LearningObject.
     */
    LearningObject *learningObject = nullptr;

    /**
     * @brief settings Pointer to the current Settings.
     */
    Settings* settings = nullptr;

    /**
     * @brief connect_learningObjectSlots Method that connects every new learningObject with the neccessary slots.
     */
    void connect_learningObjectSlots();

protected:
    /**
     * @brief resizeEvent Overload of the window's resizeEvent.
     * @param event Pointer to the QResizeEvent.
     */
    void resizeEvent(QResizeEvent *event);

    /**
     * @brief closeEvent Overload of the window's closeEvent.
     * @param event Pointer to the QCloseEvent.
     */
    void closeEvent(QCloseEvent *event);

};
#endif // HDBMAINWINDOW_H
