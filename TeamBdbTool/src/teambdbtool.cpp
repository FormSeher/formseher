#include "teambdbtool.h"
#include "ui_teambdbtool.h"
#include "choosealgdialog.h"
#include "committodbdialog.h"

#include <QFileDialog>
#include <QWidgetItem>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QColorDialog>

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
    allLinesPen = QPen(Qt::black);
    selectedLinesPen = QPen(Qt::green);
    allLinesSelectedColor = Qt::black;
    SelectedLinesSelectedColor = Qt::blue;

    //Set up the boxes

    ui->showImage->setChecked(true);
    ui->showAllFoundLines->setChecked(true);
    ui->showAllDetetectedLines->setChecked(true);
    ui->label->setPalette(allLinesPen.color());
    ui->label->setAutoFillBackground(true);
    ui->label_3->setPalette(allLinesSelectedColor);
    ui->label_3->setAutoFillBackground(true);
    ui->label_2->setPalette(selectedLinesPen.color());
    ui->label_2->setAutoFillBackground(true);
    ui->label_4->setPalette(SelectedLinesSelectedColor);
    ui->label_4->setAutoFillBackground(true);

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

        ChooseALGDialog choose(this);
        choose.setModal(true);
        choose.exec();
        lineDeteciontAlgorithm = choose.alg;
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
    std::vector<formseher::Line> result = lineDeteciontAlgorithm->calculate(input);

    QStandardItem *item;
    cv::Point2i start;
    cv::Point2i end;
    cv::Point2i previousStart;
    cv::Point2i previousEnd;
    cv::Point2i prepreviousStart;
    cv::Point2i prepreviousEnd;

    allLinesModel->clear();
    selectedLinesModel->clear();

    for(auto line : result)
    {
        start = line.getStart();
        end = line.getEnd();
        if (start != previousStart && end != previousEnd)
        {
            if (start != prepreviousStart || end != prepreviousEnd)
            {
                QString str = "";
                QTextStream (&str) << "(" << start.x << "," << start.y << ") (" << end.x << "," << end.y << ")";

                item = new QStandardItem(str);
                item->setData(QVariant(QLine(start.x, start.y, end.x, end.y)));
                allLinesModel->appendRow(item);
            }
        }
        prepreviousStart = previousStart;
        prepreviousEnd = previousEnd;
        previousStart = start;
        previousEnd = end;
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

void TeamBdbTool::on_allLinesView_clicked(const QModelIndex &index)
{
    updateAllLinesView();
    QPixmap pix = allLinesItem->pixmap();
    QPainter *painter = new QPainter(&pix);

    QPen linePen = QPen(allLinesSelectedColor);
    linePen.setWidth(5);

    QPen pointPen = QPen(Qt::black);
    pointPen.setWidth(15);

    QStandardItem *item = allLinesModel->item(index.row());
    QLine line = item->data().toLine();

    painter->setPen(pointPen);
    painter->drawPoint(line.p1());
    painter->drawPoint(line.p2());

    painter->setPen(linePen);
    painter->drawLine(line);

    delete painter;
    allLinesItem->setPixmap(pix);
}

void TeamBdbTool::on_selectedLinesView_clicked(const QModelIndex &index)
{
    updateSelectedLinesView();
    QPixmap pix = selectedLinesItem->pixmap();
    QPainter *painter = new QPainter(&pix);

    QPen linePen = QPen(SelectedLinesSelectedColor);
    linePen.setWidth(5);

    QPen pointPen = QPen(Qt::black);
    pointPen.setWidth(15);

    QStandardItem *item = selectedLinesModel->item(index.row());
    QLine line = item->data().toLine();

    painter->setPen(pointPen);
    painter->drawPoint(line.p1());
    painter->drawPoint(line.p2());

    painter->setPen(linePen);
    painter->drawLine(line);

    delete painter;
    selectedLinesItem->setPixmap(pix);
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


void TeamBdbTool::on_toolButton_clicked()
{
    QColor newColor = QColorDialog::getColor(allLinesPen.color(), this, "Pick Color");
    ui->label->setPalette(QPalette(newColor));
    allLinesPen.setColor(newColor);
    updateAllLinesView();
}

void TeamBdbTool::on_toolButton_3_clicked()
{
    QColor newColor = QColorDialog::getColor(allLinesSelectedColor, this, "Pick Color");
    allLinesSelectedColor = newColor;
    ui->label_3->setPalette(QPalette(newColor));
    updateAllLinesView();
}

void TeamBdbTool::on_toolButton_2_clicked()
{
    QColor newColor = QColorDialog::getColor(selectedLinesPen.color(), this, "Pick Color");
    ui->label_2->setPalette(QPalette(newColor));
    selectedLinesPen.setColor(newColor);
    updateSelectedLinesView();
}

void TeamBdbTool::on_toolButton_4_clicked()
{
    QColor newColor = QColorDialog::getColor(SelectedLinesSelectedColor, this, "Pick Color");
    SelectedLinesSelectedColor = newColor;
    ui->label_4->setPalette(QPalette(newColor));
    updateSelectedLinesView();
}


