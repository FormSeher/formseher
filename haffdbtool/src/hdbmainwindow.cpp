// Database tool
#include "addlinedialog.h"
#include "drawinfodialog.h"
#include "hdbmainwindow.h"
#include "learningobject.h"
#include "opencvdrawing.h"
#include "saveobjectdialog.h"
#include "settings.h"
#include "ui_hdbmainwindow.h"

// Qt
#include <QCloseEvent>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

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
    connect(ui->actionAddLine, SIGNAL(triggered()), this, SLOT(slot_actionAddLine_clicked()));
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
            connect_learningObjectSlots();

            if(dataBase != "")
                this->learningObject->setDatabase(dataBase);

            ui->widgetImage->slot_configurationChanged();
            settings->slot_settingsChanged();

            ui->tabWidget->setCurrentIndex(0);

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
                connect_learningObjectSlots();
                ui->tabWidget->setCurrentIndex(1);
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
    if( learningObject != nullptr && learningObject->getImagePath() != "")
    {
        DrawInfoDialog dialog(this);

        if(dialog.exec() == QDialog::Accepted)
        {
            learningObject->addChosenLines(OpencvDrawing::drawLines(learningObject->getOriginalImage()));
            cv::destroyWindow("Image");
        }
    }
}

void HDBMainWindow::slot_actionAddLine_clicked()
{
    AddLineDialog dialog(this);

    if(dialog.exec() == QDialog::Accepted)
    {
        if(learningObject != nullptr)
            learningObject->addChosenLine(dialog.getLine());
        else
            QMessageBox::critical(this, "Error!", "Could not save line.\nNo image loaded.");
    }
}

void HDBMainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Close", tr("Are you sure?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void HDBMainWindow::connect_learningObjectSlots()
{
    connect(ui->widgetImage, SIGNAL(signal_configurationChanged(ImageMode,int,int)), learningObject, SLOT(slot_getImage(ImageMode,int,int)));
    connect(learningObject, SIGNAL(signal_newImage(cv::Mat)), ui->widgetImage, SLOT(slot_repaint(cv::Mat)));
    connect(learningObject, SIGNAL(signal_settingsChanged()), ui->widgetImage, SLOT(slot_configurationChanged()));
    connect(settings, SIGNAL(signal_newSettings(formseher::LineDetectionAlgorithm*,std::pair<QColor,QColor>,int)),
            learningObject, SLOT(slot_setSettings(formseher::LineDetectionAlgorithm*,std::pair<QColor,QColor>,int)));
    connect(learningObject, SIGNAL(signal_linesChanged(std::pair<std::vector<formseher::Line>,std::vector<formseher::Line> >)),
            ui->widgetImage, SLOT(slot_setLines(std::pair<std::vector<formseher::Line>,std::vector<formseher::Line> >)));
    connect(ui->widgetImage, SIGNAL(signal_lineDoubleClicked(std::pair<int,int>)), learningObject, SLOT(slot_doubleClicked(std::pair<int,int>)));
    connect(learningObject, SIGNAL(signal_newDatabase(std::vector<formseher::Model>)), ui->widgetDatabase, SLOT(slot_setNewDatabase(std::vector<formseher::Model>)));
    connect(ui->widgetDatabase, SIGNAL(signal_deleteDatabaseModel(QString)), learningObject, SLOT(slot_deleteFromDataBase(QString)));
}
