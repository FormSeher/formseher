#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QColorDialog>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "hdbmainwindow.h"
#include "ui_hdbmainwindow.h"
#include "ui_linelistwidget.h"
#include "linedetection/edl/edl.h"
#include "linedetection/hough/hough.h"

HDBMainWindow::HDBMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HDBMainWindow)
{
    ui->setupUi(this);

    ui->allLineListWidget->findChild<QLabel*>("lineListLabel")->setText("Picturelines");
    ui->selectedLineListWidget->findChild<QLabel*>("lineListLabel")->setText("Objectlines");

    ui->colorChooserWidget->setDefaultColor(QColor(Qt::red));
    ui->colorChooserWidget->setSelectedColor(QColor(Qt::green));

    connectMySlots();
}

HDBMainWindow::~HDBMainWindow()
{
    delete ui;
}

void HDBMainWindow::openImage_clicked()
{
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr("Image files (*.png *.jpg *.bmp)"));

        image = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
        if( ! image.data )
        {
            std::cerr << "Unable to load image!" << std::endl;
        }
        ui->imageWidget->setImage(fileName, image);

        doAlgorithmWork();
    }
    catch(int e)
    {
        std::cout << "Error: Could not open picture." << std::endl;
    }
}

void HDBMainWindow::connectMySlots()
{
    connect(ui->openImageAction, SIGNAL(triggered()), this, SLOT(openImage_clicked()));
    connect(ui->colorChooserWidget, SIGNAL(colorUpdated()), this, SLOT(repaintImage()));
    connect(ui->imageWidget, SIGNAL(imageModeChanged()), this, SLOT(repaintImage()));

    connect(ui->allLineListWidget, SIGNAL(itemSelected(int)), this, SLOT(allLineSelection(int)));
    connect(ui->selectedLineListWidget, SIGNAL(itemSelected(int)), this, SLOT(selectedLineSelection(int)));

    connect(ui->allLineListWidget, SIGNAL(myItemDoubleClicked(int)), this, SLOT(doubleClickedFoundLines(int)));
    connect(ui->selectedLineListWidget, SIGNAL(myItemDoubleClicked(int)), this, SLOT(doubleClickedSelectedLines(int)));
}

void HDBMainWindow::allLineSelection(int i)
{
    repaintImage(i, true);
}

void HDBMainWindow::selectedLineSelection(int i)
{
    repaintImage(i, false);
}

void HDBMainWindow::doAlgorithmWork()
{
    // TODO: Change to EDL newest version. Used hough for better results.
    formseher::Hough edl = formseher::Hough();
    foundLines = edl.calculate(image);
    selectedLines.clear();
    ui->allLineListWidget->clearLineList();
    ui->selectedLineListWidget->clearLineList();
    ui->allLineListWidget->setLineList(foundLines);
    repaintImage(0,true);
}

void HDBMainWindow::repaintImage()
{
    if(foundLines.size() > 0)
    {
        ui->imageWidget->repaintImage(selectedLines, formseher::Line(0,0,0,0),
                                  ui->colorChooserWidget->getDefaultColor(),ui->colorChooserWidget->getSelectedColor());
    }
}

void HDBMainWindow::repaintImage(int i=0, bool firstList=true)
{
    if(foundLines.size() > 0)
    {
        if(firstList)
        {
            ui->imageWidget->repaintImage(selectedLines, foundLines[i],
                                  ui->colorChooserWidget->getDefaultColor(),ui->colorChooserWidget->getSelectedColor());
        } else {
            ui->imageWidget->repaintImage(selectedLines, selectedLines[i],
                                      ui->colorChooserWidget->getDefaultColor(),ui->colorChooserWidget->getSelectedColor());
        }
    }
}

void HDBMainWindow::doubleClickedFoundLines(int i)
{
    selectedLines.push_back(foundLines[i]);
    foundLines.erase(foundLines.begin()+i);

    ui->allLineListWidget->setLineList(foundLines);
    ui->selectedLineListWidget->setLineList(selectedLines);
}

void HDBMainWindow::doubleClickedSelectedLines(int i)
{
    foundLines.push_back(selectedLines[i]);
    selectedLines.erase(selectedLines.begin()+i);

    ui->allLineListWidget->setLineList(foundLines);
    ui->selectedLineListWidget->setLineList(selectedLines);
}
