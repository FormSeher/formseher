#ifndef QLISTWIDGETOBJECT_H
#define QLISTWIDGETOBJECT_H

#include <QListWidgetItem>
#include "objectdetection/model.h"

class QListWidgetObject : public QListWidgetItem
{
public:
    QListWidgetObject();

    formseher::Model getModel() const;
    void setModel(formseher::Model model);

private:
    formseher::Model model;
};

#endif // QLISTWIDGETOBJECT_H
