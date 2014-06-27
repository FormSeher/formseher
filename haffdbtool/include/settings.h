#ifndef SETTINGS_H
#define SETTINGS_H

// Formseher project
#include "linedetection/linedetectionalgorithm.h"

// Qt
#include <QMainWindow>

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
