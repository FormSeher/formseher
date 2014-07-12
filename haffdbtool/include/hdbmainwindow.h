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

class HDBMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HDBMainWindow(QWidget *parent = 0);
    ~HDBMainWindow();

signals:
    void signal_statusChange(QString);
    void signal_windowResize();


private slots:
    void slot_actionOpenImage_clicked();
    void slot_actionCreateDatabase_clicked();
    void slot_actionOpenDatabase_clicked();
    void slot_actionSaveObject_clicked();
    void slot_actionSettings_clicked();
    void slot_actionDraw_clicked();
    void slot_actionAddLine_clicked();

private:
    Ui::HDBMainWindow* ui;

    LearningObject *learningObject = nullptr;
    Settings* settings = nullptr;

    void connect_learningObjectSlots();

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

};
#endif // HDBMAINWINDOW_H
