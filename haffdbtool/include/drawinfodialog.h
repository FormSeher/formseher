#ifndef DRAWINFODIALOG_H
#define DRAWINFODIALOG_H

// Qt
#include <QDialog>

namespace Ui {
class DrawInfoDialog;
}

class DrawInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawInfoDialog(QWidget *parent = 0);
    ~DrawInfoDialog();

private slots:
    void slot_toggleShow(bool value);
    virtual int exec();

private:
    Ui::DrawInfoDialog *ui;

    static bool showEverytime;
};

#endif // DRAWINFODIALOG_H
