#ifndef ADDLINEDIALOG_H
#define ADDLINEDIALOG_H

// Formseher project
#include "line.h"

// Qt
#include <QDialog>

namespace Ui {
class AddLineDialog;
}

/**
 * @brief The AddLineDialog class is a Qt UI class which
 * represents a widget to add a line based on two coordinates.
 */
class AddLineDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief AddLineDialog standard constructor.
     * @param parent Parent widget.
     */
    explicit AddLineDialog(QWidget *parent = 0);

    /**
     * @brief AddLineDialog destructor.
     */
    ~AddLineDialog();

    /**
     * @brief getLine Getter function for the constructed line.
     * @return Constructed Line.
     */
    formseher::Line getLine();

private:
    Ui::AddLineDialog *ui;
};

#endif // ADDLINEDIALOG_H
