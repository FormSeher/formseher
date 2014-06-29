#include "committodbdialog.h"
#include "ui_committodbdialog.h"

commitToDBDialog::commitToDBDialog(formseher::Object obj, QString dbFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commitToDBDialog),
    obj(obj),
    dbFile(dbFile)
{
    ui->setupUi(this);

    //work the string for better output
    QString str = QString::fromStdString(obj.toString());
    str.replace(":", ":\n");
    str.replace(";", "\n");

    ui->textBrowser->setText(str);
}

commitToDBDialog::~commitToDBDialog()
{
    delete ui;
}

void commitToDBDialog::on_buttonBox_accepted()
{
     formseher::DatabaseUtils dbu(dbFile.toStdString());

     dbu.read(); //call read before we write

     dbu.addObject(obj);
     dbu.write();
}
