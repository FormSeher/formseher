#include "hdbmainwindow.h"
#include "ui_hdbmainwindow.h"
#include "learningobject.h"
#include "settings.h"
#include "opencvdrawing.h"
#include "saveobjectdialog.h"

#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>

#include <iostream>

HDBMainWindow::HDBMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HDBMainWindow)
{
    ui->setupUi(this);

    settings = new Settings();

    // Slot connection
    connect(ui->actionOpenImage, SIGNAL(triggered()), this, SLOT(slot_actionOpenImage_clicked()));
    connect(ui->actionOpenDatabase, SIGNAL(triggered()), this, SLOT(slot_actionOpenDatabase_clicked()));
    connect(ui->actionSaveObject, SIGNAL(triggered()), this, SLOT(slot_actionSaveObject_clicked()));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(slot_actionSettings_clicked()));
    connect(this, SIGNAL(signal_statusChange(QString)), ui->statusBar, SLOT(showMessage(QString)));
    connect(this, SIGNAL(signal_windowResize()), ui->widgetImage, SLOT(slot_configurationChanged()));
    connect(ui->actionDraw, SIGNAL(triggered()), this, SLOT(slot_actionDraw_clicked()));
}

HDBMainWindow::~HDBMainWindow()
{
    delete ui;
}

void HDBMainWindow::slot_actionOpenImage_clicked()
{
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr("Image files (*.png *.jpg *.bmp)"));

        if( QFile(fileName).exists() )
        {
            QString dataBase = "";
            if(this->learningObject != nullptr)
            {
                dataBase = this->learningObject->getDatabasePath();
                learningObject->~LearningObject();
            }

            this->learningObject = new LearningObject(fileName);

            //Connect every new learning object
            connect(ui->widgetImage, SIGNAL(signal_configurationChanged(ImageMode,int,int)), learningObject, SLOT(slot_getImage(ImageMode,int,int)));
            connect(learningObject, SIGNAL(signal_newImage(cv::Mat)), ui->widgetImage, SLOT(slot_repaint(cv::Mat)));
            connect(learningObject, SIGNAL(signal_settingsChanged()), ui->widgetImage, SLOT(slot_configurationChanged()));
            connect(settings, SIGNAL(signal_newSettings(formseher::LineDetectionAlgorithm*,std::pair<QColor,QColor>,int)),
                    learningObject, SLOT(slot_setSettings(formseher::LineDetectionAlgorithm*,std::pair<QColor,QColor>,int)));
            connect(learningObject, SIGNAL(signal_linesChanged(std::pair<std::vector<formseher::Line>,std::vector<formseher::Line> >)),
                    ui->widgetImage, SLOT(slot_setLines(std::pair<std::vector<formseher::Line>,std::vector<formseher::Line> >)));
            connect(ui->widgetImage, SIGNAL(signal_lineDoubleClicked(std::pair<int,int>)), learningObject, SLOT(slot_doubleClicked(std::pair<int,int>)));
            connect(learningObject, SIGNAL(signal_newDatabase(std::vector<formseher::Model>)), ui->widgetDatabase, SLOT(slot_setNewDatabase(std::vector<formseher::Model>)));

            if(dataBase != "")
                this->learningObject->setDatabase(dataBase);

            ui->widgetImage->slot_configurationChanged();
            settings->slot_settingsChanged();

            signal_statusChange(QString("Loaded Image..." + fileName));
        }
    }
    catch(int e)
    {
        QMessageBox::critical(this, "Error!", "Could not open image.");
    }
}

void HDBMainWindow::slot_actionOpenDatabase_clicked()
{
    try
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open database"), QDir::homePath(), tr("Database file (*.json)"));

        if( QFile(fileName).exists() )
        {
            if(this->learningObject == nullptr)
            {
                learningObject = new LearningObject(QString(""));
            }

            this->learningObject->setDatabase(fileName);

            signal_statusChange(QString("Loaded Database..." + fileName));
        }
    }
    catch(int e)
    {
        QMessageBox::critical(this, "Error!", "Could not open database.");
    }
}

void HDBMainWindow::slot_actionSaveObject_clicked()
{
    if(learningObject != nullptr)
    {
        if(learningObject->getDatabasePath() != "")
        {
            SaveObjectDialog dialog(this);

            if(dialog.exec() == QDialog::Accepted)
            {
                if( dialog.getObjectName() != "")
                {
                    learningObject->saveToDatabase(dialog.getObjectName());

                    emit signal_statusChange("Saved Object '" + dialog.getObjectName() + "' to database " + learningObject->getDatabasePath());
                }
                else
                {
                    QMessageBox::critical(this, "Error!", "Could not save object.\nNo object name!");
                }
            }
        }
        else
        {
            QMessageBox::critical(this, "Error!", "Could not save object.\nNo database loaded!");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error!", "Could not save object.\nNo image loaded.");
    }
}

void HDBMainWindow::slot_actionSettings_clicked()
{
    settings->move(this->rect().center() - settings->rect().center());
    settings->show();
}

void HDBMainWindow::resizeEvent (QResizeEvent *event)
{
    emit signal_windowResize();
}

void HDBMainWindow::slot_actionDraw_clicked()
{
    //OpencvDrawing::drawLines(learningObject->getOriginalImage());
}
