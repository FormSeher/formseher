#ifndef EDLCONFIGDIALOG_H
#define EDLCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class EDLConfigDialog;
}

class EDLConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EDLConfigDialog(QWidget *parent = 0);
    ~EDLConfigDialog();

private:
    Ui::EDLConfigDialog *ui;
};

#endif // EDLCONFIGDIALOG_H
