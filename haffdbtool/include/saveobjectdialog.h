#ifndef SAVEOBJECTDIALOG_H
#define SAVEOBJECTDIALOG_H

// Qt
#include <QDialog>

namespace Ui {
class SaveObjectDialog;
}

/**
 * @brief The Settings class is a Qt UI class wich represents the save object dialog.
 */
class SaveObjectDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief SaveObjectDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit SaveObjectDialog(QWidget *parent = 0);

    /**
     * @brief SaveObjectDialog destructor.
     */
    ~SaveObjectDialog();

    /**
     * @brief getObjectName Getter for the typed object name.
     * @return Typed objectname.
     */
    QString getObjectName() const;

private:
    Ui::SaveObjectDialog *ui;
};

#endif // SAVEOBJECTDIALOG_H
