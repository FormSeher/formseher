#ifndef COMMITTODBDIALOG_H
#define COMMITTODBDIALOG_H

#include <QDialog>

#include <objectdetection/databaseutils.h>

namespace Ui
{
class commitToDBDialog;
}

class commitToDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit commitToDBDialog(formseher::Object obj, QString dbFile, QWidget *parent = 0);
    ~commitToDBDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::commitToDBDialog *ui;
    formseher::Object obj;
    QString dbFile;
};

#endif // COMMITTODBDIALOG_H
