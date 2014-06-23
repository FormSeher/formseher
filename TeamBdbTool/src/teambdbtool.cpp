#include "teambdbtool.h"
#include "ui_teambdbtool.h"
#include "choosealgdialog.h"
#include "committodbdialog.h"

#include <QFileDialog>
#include <QWidgetItem>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsItem>

#include <line.h>
#include <objectdetection/databaseutils.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

TeamBdbTool::TeamBdbTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeamBdbTool)
{
    ui->setupUi(this);

    //set up the models and listviews

    allLinesModel = new QStandardItemModel(this);
    selectedLinesModel = new QStandardItemModel(this);
    ui->allLinesView->setModel(allLinesModel);
    ui->selectedLinesView->setModel(selectedLinesModel);
    ui->allLinesView->show();
    ui->selectedLinesView->show();

    //set up color items
    allLinesPen = QPen(Qt::red);
    selectedLinesPen = QPen(Qt::green);

    //Set up the checkboxes

    ui->showImage->setChecked(true);
    ui->showAllFoundLines->setChecked(true);
    ui->showAllDetetectedLines->setChecked(true);

    //Set up the Graphicsview

    scene = new QGraphicsScene(this);

    image = new QGraphicsPixmapItem();
    allLinesItem = new QGraphicsPixmapItem();
    selectedLinesItem = new QGraphicsPixmapItem();

    scene->addItem(image);
    image->setEnabled(false);
    scene->addItem(allLinesItem);
    scene->addItem(selectedLinesItem);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

TeamBdbTool::~TeamBdbTool()
{
    delete allLinesModel;
    delete selectedLinesModel;
    delete scene;
    delete image;
    delete allLinesItem;
    delete selectedLinesItem;
    delete ui;
}

void TeamBdbTool::on_actionDatei_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(
                            this,
                            tr("Datei öffnen"),
                            "//",
                            "All files (*.*)"
                           );

    if (fileName.isEmpty())
    {
        QMessageBox::information(this, tr("TeamBdbTool"),
                                 tr("Cannot load %1.").arg(fileName));
        return;

     }
    else
    {

        QPixmap pix = QPixmap(fileName);
        image->setPixmap(QPixmap(pix));
        ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

        ChooseALGDialog choose(lineDeteciontAlgorithm, this);
        choose.setModal(true);
        choose.exec();
        runAlgorithm(fileName);
        updateView();
    }
}

void TeamBdbTool::on_actionOrdner_triggered()
{
    QString fileDirectory = QFileDialog::getExistingDirectory(this,
                                                 tr("Ordner auswählen"),
                                                 "//",
                                                 QFileDialog::ShowDirsOnly
                                                );
}

void TeamBdbTool::on_showImage_clicked()
{
    if (ui->showImage->isChecked())
    {
        image->setVisible(true);
    }
    else
    {
        image->setVisible(false);
    }
}

void TeamBdbTool::on_showAllFoundLines_clicked()
{
    if (ui->showAllFoundLines->isChecked())
    {
        allLinesItem->setVisible(true);
    }
    else
    {
        allLinesItem->setVisible(false);
    }
}

void TeamBdbTool::on_showAllDetetectedLines_clicked()
{
    if (ui->showAllDetetectedLines->isChecked())
    {
        selectedLinesItem->setVisible(true);
    }
    else
    {
        selectedLinesItem->setVisible(false);
    }
}

void TeamBdbTool::runAlgorithm(QString fileName)
{
    cv::Mat input = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

    lineDeteciontAlgorithm = new formseher::EDL2();
    std::vector<formseher::Line> result = lineDeteciontAlgorithm->calculate(input);

    QStandardItem *item;

    for(auto line : result)
    {
        cv::Point2i start = line.getStart();
        cv::Point2i end = line.getEnd();
        QString str = "";
        QTextStream (&str) << "(" << start.x << "," << start.y << ") (" << end.x << "," << end.y << ")";

        item = new QStandardItem(str);
        item->setData(QVariant(QLine(start.x, start.y, end.x, end.y)));
        allLinesModel->appendRow(item);
    }
}
void TeamBdbTool::resizeEvent (QResizeEvent * event)
{
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void TeamBdbTool::updateView()
{
    updateAllLinesView();
    updateSelectedLinesView();
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void TeamBdbTool::updateAllLinesView()
{
    QPixmap pix = QPixmap(image->pixmap().size());
    pix.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pix);
    painter->setPen(allLinesPen);
    QStandardItem *item;
    QLine line;
    for (int row = 0; row < allLinesModel->rowCount(); ++row)
    {
        item = allLinesModel->item(row);
        line = item->data().toLine();
        painter->drawLine(line);
    }

    delete painter;
    allLinesItem->setPixmap(pix);
}

void TeamBdbTool::updateSelectedLinesView()
{
    QPixmap pix = QPixmap(image->pixmap().size());
    pix.fill(Qt::transparent);
    QPainter *painter = new QPainter(&pix);
    painter->setPen(selectedLinesPen);
    QStandardItem *item;
    QLine line;
    for (int row = 0; row < selectedLinesModel->rowCount(); ++row)
    {
        item = selectedLinesModel->item(row);
        line = item->data().toLine();
        painter->drawPoint(line.p1());
        painter->drawPoint(line.p2());
        painter->drawLine(line);
    }
    delete painter;
    selectedLinesItem->setPixmap(pix);
}

void TeamBdbTool::on_allLinesView_doubleClicked(const QModelIndex &index)
{
    selectedLinesModel->appendRow(allLinesModel->takeRow(index.row()));
    updateView();
}

void TeamBdbTool::on_selectedLinesView_doubleClicked(const QModelIndex &index)
{
    allLinesModel->appendRow(selectedLinesModel->takeRow(index.row()));
    updateView();
}
void TeamBdbTool::on_action_ffnen_Erstellen_triggered()
{
    dbFile = QFileDialog::getOpenFileName(
                             this,
                             tr("Datei aauswählen"),
                             "//",
                             "json files (*.json)"
                            );

     if (dbFile.isEmpty())
     {
         QMessageBox::information(this, tr("TeamBdbTool"),
                                  tr("Cannot load %1.").arg(dbFile));
         return;

      }
     else
     {
        ui->actionDatenschreiben->setEnabled(true);
     }
}

void TeamBdbTool::on_actionDatenschreiben_triggered()
{
    formseher::Object obj;

    QStandardItem *item;
    QLine line;

    for (int row = 0; row < selectedLinesModel->rowCount(); ++row)
    {
        item = selectedLinesModel->item(row);
        line = item->data().toLine();
        obj.addLine(formseher::Line(line.x1(),line.y1(),line.x2(),line.y2()));
        obj.setName("justTesting");
    }

    commitToDBDialog commit(obj, dbFile, this);
    commit.setModal(true);
    commit.exec();
}
