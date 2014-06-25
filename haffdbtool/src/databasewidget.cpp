#include "include/databasewidget.h"
#include "ui_databasewidget.h"
#include "objectdetection/model.h"
#include "qlistwidgetobject.h"

#include <iostream>

databaseWidget::databaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseWidget)
{
    ui->setupUi(this);
}

databaseWidget::~databaseWidget()
{
    delete ui;
}

void databaseWidget::slot_setNewDatabase(std::vector<formseher::Model> models)
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

        obj->setModel(model);
        obj->setText(tr(listtext.str().c_str()));

        ui->listWidgetObjects->addItem(obj);
    }

}

//void databaseWidget::slot_deleteModel()
//{
//    //emit signal_deleteDatabaseModel(QString(ui->listWidgetObjects->))
//}
