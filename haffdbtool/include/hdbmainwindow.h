#ifndef HDBMAINWINDOW_H
#define HDBMAINWINDOW_H

#include <QMainWindow>
#include <linelistwidget.h>
#include <imagewidget.h>
#include <ui_hdbmainwindow.h>
#include <QColorDialog>

namespace Ui {
class HDBMainWindow;
}

class HDBMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HDBMainWindow(QWidget *parent = 0);
    ~HDBMainWindow();

public slots:
    void openImage_clicked();
    void repaintImage();
    void repaintImage(int i, bool firstList);
    void allLineSelection(int i);
    void selectedLineSelection(int i);

public slots:
    void doubleClickedFoundLines(int i);
    void doubleClickedSelectedLines(int i);

private:
    Ui::HDBMainWindow *ui;

    void connectMySlots();
    void doAlgorithmWork();

    cv::Mat image;
    std::vector<formseher::Line> foundLines;
    std::vector<formseher::Line> selectedLines;
};

#endif // HDBMAINWINDOW_H
