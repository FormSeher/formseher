#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include "linedetection/linedetectionalgorithm.h"

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

signals:
    void signal_newSettings(formseher::LineDetectionAlgorithm*, std::pair<QColor, QColor>, int);

public slots:
    void slot_settingsChanged();

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
