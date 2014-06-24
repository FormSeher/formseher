#ifndef HDBMAINWINDOW_H
#define HDBMAINWINDOW_H

#include <QMainWindow>

#include "learningobject.h"
#include "settings.h"

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
    void slot_actionOpenDatabase_clicked();
    void slot_actionSaveObject_clicked();
    void slot_actionSettings_clicked();
    void slot_actionDraw_clicked();

private:
    Ui::HDBMainWindow* ui;

    LearningObject *learningObject = nullptr;
    Settings* settings = nullptr;

    virtual void resizeEvent (QResizeEvent *event);
};
#endif // HDBMAINWINDOW_H
