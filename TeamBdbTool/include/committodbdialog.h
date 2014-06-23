#ifndef COMMITTODBDIALOG_H
#define COMMITTODBDIALOG_H

#include <QDialog>

namespace Ui {
class commitToDBDialog;
}

class commitToDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit commitToDBDialog(QWidget *parent = 0);
    ~commitToDBDialog();

private:
    Ui::commitToDBDialog *ui;
};

#endif // COMMITTODBDIALOG_H
