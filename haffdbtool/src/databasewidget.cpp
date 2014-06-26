#include "include/databasewidget.h"
#include "ui_databasewidget.h"
#include "objectdetection/model.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include <QVariant>
#include <QLabel>
#include <QDialog>

DatabaseWidget::DatabaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseWidget)
{
    ui->setupUi(this);

    // Slot connection
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(slot_deleteModel()));
    connect(ui->pushButtonDraw, SIGNAL(clicked()), this, SLOT(slot_drawModel()));
}

DatabaseWidget::~DatabaseWidget()
{
    delete ui;
}

void DatabaseWidget::slot_setNewDatabase(std::vector<formseher::Model> models)
{

    ui->listWidgetObjects->clear();


    for(formseher::Model model : models)
    {
        QListWidgetItem* obj = new QListWidgetItem;

        std::stringstream listtext;
        listtext << std::endl << "Model: " << model.getName() << std::endl;
        listtext << "Lines: ";

        for(auto line : model.getLines())
            listtext << line->getStart() << " → " << line->getEnd() << "; ";

        listtext << std::endl;

        QString objectString = QString::fromStdString(model.toString());
        QVariant objectStringData(objectString);
        obj->setData(Qt::UserRole, objectStringData);

        obj->setText(tr(listtext.str().c_str()));

        ui->listWidgetObjects->addItem(obj);

    }

}

void DatabaseWidget::slot_deleteModel()
{
   QVariant data = ui->listWidgetObjects->currentItem()->data(Qt::UserRole);
   emit signal_deleteDatabaseModel(data.toString());
}

void DatabaseWidget::slot_drawModel()
{
    if( ui->listWidgetObjects->currentRow() < 0)
        return;

    formseher::Model model;
    model.fromString( ui->listWidgetObjects->currentItem()->data(Qt::UserRole).toString().toStdString());

    cv::Mat img = cv::Mat::zeros(model.getBoundingBox().size().height, model.getBoundingBox().size().width, CV_8UC3);

    for(const formseher::Line* line : model.getLines())
    {
        cv::Point2i myStart (line->getStart().x - model.getBoundingBox().x, line->getStart().y - model.getBoundingBox().y);
        cv::Point2i myEnd   (line->getEnd().x - model.getBoundingBox().x, line->getEnd().y - model.getBoundingBox().y);

        cv::line(img, myStart, myEnd, cv::Scalar(255, 200, 155));
    }

    QImage qImg = QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    QDialog* dialog = new QDialog();
    QGridLayout* layout = new QGridLayout();
    QLabel* imgLabel = new QLabel("");

    imgLabel->setPixmap(QPixmap::fromImage(qImg));
    imgLabel->adjustSize();

    layout->addWidget(imgLabel,0,0);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    dialog->setLayout(layout);
    dialog->setWindowTitle(QString::fromStdString(model.getName()));
    dialog->setWindowFlags(Qt::WindowCloseButtonHint);
    dialog->setAttribute( Qt::WA_DeleteOnClose, true );
    dialog->setModal(true);

    dialog->show();
}
