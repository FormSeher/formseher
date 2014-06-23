#include "teambdbtool.h"
#include "ui_teambdbtool.h"
#include <QFileDialog>
#include <QStringListModel>
#include <QWidgetItem>
#include <QTextStream>
#include <QMessageBox>
#include <line.h>

#include "choosealgdialog.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



TeamBdbTool::TeamBdbTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeamBdbTool)
{
    ui->setupUi(this);

    //set up the models and listviews

    allLines = new QStandardItemModel(this);
    selecteLines = new QStandardItemModel(this);
    ui->allLinesView->setModel(allLines);
    ui->selectedLinesView->setModel(selecteLines);
    ui->allLinesView->show();
    ui->selectedLinesView->show();

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
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
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

        ChooseALGDialog choose(lineDeteciontAlgorithm, this);
        choose.setModal(true);
        choose.exec();
        runAlgorithm(fileName);
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
    if (ui->showAllFoundLines->isChecked())
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
        allLines->appendRow(item);
    }
}

//void TeamBdbTool::runAlgorithm(QString fileName)
//{
//    cv::Mat input = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

//    lineDeteciontAlgorithm = new formseher::EDL2();
//    std::vector<formseher::Line> result = lineDeteciontAlgorithm->calculate(input);

//    QPixmap pix = QPixmap(image->pixmap().size());
//    pix.fill(Qt::transparent);
//    QPainter *painter = new QPainter(&pix);
//    QPen pen(Qt::red);
//    pen.setWidth(1);
//    painter->setPen(pen);

//    for(auto line : result)
//    {
//        cv::Point2i start = line.getStart();
//        cv::Point2i end = line.getEnd();

//        painter->drawLine(QPoint(start.x, start.y),QPoint(end.x, end.y));
//    }
//    delete painter;
//    drawing->setPixmap(pix);
//}


void TeamBdbTool::on_allLinesView_doubleClicked(const QModelIndex &index)
{
    selecteLines->appendRow(allLines->takeRow(index.row()));
}

void TeamBdbTool::on_selectedLinesView_doubleClicked(const QModelIndex &index)
{
    allLines->appendRow(selecteLines->takeRow(index.row()));
}
