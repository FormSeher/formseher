#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

// Formseher project
#include "objectdetection/model.h"

// Qt
#include <QWidget>

namespace Ui {
class databaseWidget;
}

/**
 * @brief The DatabaseWidget class is a Qt UI class which displays the content
 * of the loaded database.
 */
class DatabaseWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief DatabaseWidget standard constructor.
     * @param parent Parent widget.
     */
    explicit DatabaseWidget(QWidget *parent = 0);

    /**
     * @brief DatabaseWidget destructor.
     */
    ~DatabaseWidget();

signals:
    /**
     * @brief signal_deleteDatabaseModel Signal that gets emmited if a database model should be deleted.
     */
    void signal_deleteDatabaseModel(QString);

public slots:
    /**
     * @brief slot_setNewDatabase Slot that gets connected to learning objects and sets the models to the listView.
     * @param models Models to be set to the listView.
     */
    void slot_setNewDatabase(std::vector<formseher::Model> models);

    /**
     * @brief slot_deleteModel Slot that gets connected to the 'Delete' button.
     */
    void slot_deleteModel();

private slots:
    /**
     * @brief slot_drawModel Slot that gets connected to the 'Draw' button.
     */
    void slot_drawModel();


private:
    Ui::databaseWidget *ui;
};

#endif // DATABASEWIDGET_H
