#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

// Formseher project
#include "objectdetection/model.h"

// Qt
#include <QWidget>

namespace Ui {
class databaseWidget;
}

class DatabaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseWidget(QWidget *parent = 0);
    ~DatabaseWidget();

signals:
    void signal_deleteDatabaseModel(QString);

public slots:
    void slot_setNewDatabase(std::vector<formseher::Model> models);
    void slot_deleteModel();

private slots:
    void slot_drawModel();


private:
    Ui::databaseWidget *ui;
};

#endif // DATABASEWIDGET_H
