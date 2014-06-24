#ifndef SAVEOBJECTDIALOG_H
#define SAVEOBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class SaveObjectDialog;
}

class SaveObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveObjectDialog(QWidget *parent = 0);
    ~SaveObjectDialog();

    QString getObjectName() const;

private:
    Ui::SaveObjectDialog *ui;
};

#endif // SAVEOBJECTDIALOG_H
