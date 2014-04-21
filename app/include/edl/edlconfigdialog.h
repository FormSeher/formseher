#ifndef EDLCONFIGDIALOG_H
#define EDLCONFIGDIALOG_H

#include <QDialog>

#include "algorithmconfigdialog.h"

namespace Ui {
class EDLConfigDialog;
}

class EDLConfigDialog : public AlgorithmConfigDialog
{
    Q_OBJECT

public:
    explicit EDLConfigDialog(QWidget *parent = 0);
    ~EDLConfigDialog();

    Algorithm* getAlgorithm();

private:
    Ui::EDLConfigDialog *ui;
};

#endif // EDLCONFIGDIALOG_H
