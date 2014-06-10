#ifndef FS_HAFFCONFIGDIALOG_H
#define FS_HAFFCONFIGDIALOG_H

#include <QDialog>

#include "gui/objectdetection/objectdetectionalgorithmconfigdialog.h"

namespace Ui {
class HaffConfigDialog;
}

namespace formseher
{

class ObjectDetectionAlgorithm;

class HaffConfigDialog : public ObjectDetectionAlgorithmConfigDialog
{
    Q_OBJECT

public:
    explicit HaffConfigDialog(QWidget *parent = 0);
    ~HaffConfigDialog();

    ObjectDetectionAlgorithm* createAlgorithm();

private:
    Ui::HaffConfigDialog *ui;
};

} // namespace formseher

#endif // FS_HAFFCONFIGDIALOG_H
