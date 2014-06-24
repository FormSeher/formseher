#ifndef TEAMBDBTOOL_H
#define TEAMBDBTOOL_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringListModel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStandardItemModel>
#include <line.h>
#include <linedetection/linedetectionalgorithm.h>
#include <linedetection/edl/edl.h>
#include <linedetection/edl2/edl2.h>
#include <linedetection/hough/hough.h>

namespace Ui {
class TeamBdbTool;
}

class TeamBdbTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeamBdbTool(QWidget *parent = 0);
    ~TeamBdbTool();

private slots:
    void on_actionDatei_triggered();
    void on_actionOrdner_triggered();
    void on_showImage_clicked();
    void on_showAllFoundLines_clicked();
    void on_showAllDetetectedLines_clicked();
    void on_allLinesView_doubleClicked(const QModelIndex &index);
    void on_selectedLinesView_doubleClicked(const QModelIndex &index);
    void on_action_ffnen_Erstellen_triggered();
    void on_actionDatenschreiben_triggered();
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

protected:

    void resizeEvent (QResizeEvent * event);

private:

    void runAlgorithm(QString filename);
    void updateView();
    void updateAllLinesView();
    void updateSelectedLinesView();


    Ui::TeamBdbTool *ui;

    //Graphicsview
    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;
    QGraphicsPixmapItem *allLinesItem;
    QGraphicsPixmapItem *selectedLinesItem;
    QGraphicsPixmapItem *pixAllFoundLines;
    QGraphicsPixmapItem *pixAllSelectedLines;

    QPen allLinesPen;
    QPen selectedLinesPen;

    //Listview
    QStandardItemModel *allLinesModel;
    QStandardItemModel *selectedLinesModel;

    formseher::LineDetectionAlgorithm* lineDeteciontAlgorithm;

    QString dbFile;


};

#endif // TEAMBDBTOOL_H
