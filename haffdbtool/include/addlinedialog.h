#ifndef ADDLINEDIALOG_H
#define ADDLINEDIALOG_H

#include <QDialog>

#include "line.h"

namespace Ui {
class AddLineDialog;
}

class AddLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineDialog(QWidget *parent = 0);
    ~AddLineDialog();

    formseher::Line getLine();

private:
    Ui::AddLineDialog *ui;
};

#endif // ADDLINEDIALOG_H
