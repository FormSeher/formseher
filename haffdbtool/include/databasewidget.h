#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include "objectdetection/model.h"

namespace Ui {
class databaseWidget;
}

class databaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit databaseWidget(QWidget *parent = 0);
    ~databaseWidget();

public slots:
    void slot_setNewDatabase(std::vector<formseher::Model> models);

private:
    Ui::databaseWidget *ui;
};

#endif // DATABASEWIDGET_H
