#ifndef DRAWINFODIALOG_H
#define DRAWINFODIALOG_H

// Qt
#include <QDialog>

namespace Ui {
class DrawInfoDialog;
}

/**
 * @brief The DrawInfoDialog class is a Qt UI class which
 * displays a dialog with information about drawing.
 */
class DrawInfoDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DrawInfoDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit DrawInfoDialog(QWidget *parent = 0);

    /**
     * @brief DrawInfoDialog destructor.
     */
    ~DrawInfoDialog();

    /**
     * @brief exec Overload of the QDialog exec function.
     * @return Return if the dialog got accepted.
     */
    virtual int exec();

private slots:
    /**
     * @brief slot_toggleShow Slot that gets connected to the "Show everytime" checkbox.
     * @param value Indication if "Show everytime" is checked.
     */
    void slot_toggleShow(bool value);

private:
    Ui::DrawInfoDialog *ui;

    /** @brief showEverytime Hold the value of the "Show everytime" checkbox. */
    static bool showEverytime;
};

#endif // DRAWINFODIALOG_H
