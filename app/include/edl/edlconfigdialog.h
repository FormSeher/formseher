#ifndef EDLCONFIGDIALOG_H
#define EDLCONFIGDIALOG_H

#include <QDialog>

#include "algorithmconfigdialog.h"
#include "edl/edl.h"

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

    EDL edl;
};

#endif // EDLCONFIGDIALOG_H
