/*
* This file is part of FormSeher.
*
* FormSeher is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FormSeher is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2014 FormSeher
*/

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

    void on_allLinesView_clicked(const QModelIndex &index);

    void on_selectedLinesView_clicked(const QModelIndex &index);

    void on_toolButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_lineEdit_editingFinished();

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

    QPen allLinesPen;
    QPen selectedLinesPen;
    QColor allLinesSelectedColor;
    QColor SelectedLinesSelectedColor;

    //Listview
    QStandardItemModel *allLinesModel;
    QStandardItemModel *selectedLinesModel;

    formseher::LineDetectionAlgorithm* lineDeteciontAlgorithm;

    QString dbFile;
    QString objName;


};

#endif // TEAMBDBTOOL_H
