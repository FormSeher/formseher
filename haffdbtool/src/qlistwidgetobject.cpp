#include "include/qlistwidgetobject.h"

QListWidgetObject::QListWidgetObject()
    :QListWidgetItem()
{
}

formseher::Model QListWidgetObject::getModel() const
{
    return model;
}

void QListWidgetObject::setModel(formseher::Model model)
{
    this->model = model;
}
