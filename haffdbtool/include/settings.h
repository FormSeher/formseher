#ifndef SETTINGS_H
#define SETTINGS_H

// Formseher project
#include "linedetection/linedetectionalgorithm.h"

// Qt
#include <QMainWindow>

namespace Ui {
class Settings;
}

/**
 * @brief The Settings class is a Qt UI class wich represents the settings dialog.
 */
class Settings : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Settings standard constructor.
     * @param parent Parent widget.
     */
    explicit Settings(QWidget *parent = 0);

    /**
     * @brief Settings destructor.
     */
    ~Settings();

signals:
    /**
     * @brief signal_newSettings Signal that gets emmited if new settings get saved.
     */
    void signal_newSettings(formseher::LineDetectionAlgorithm*, std::pair<QColor, QColor>, int);

public slots:
    /**
     * @brief slot_settingsChanged Slot that gets connected to the accept/deny button in settings dialog.
     */
    void slot_settingsChanged();

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
