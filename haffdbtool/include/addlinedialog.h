#ifndef ADDLINEDIALOG_H
#define ADDLINEDIALOG_H

// Formseher project
#include "line.h"

// Qt
#include <QDialog>

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
