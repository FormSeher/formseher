#ifndef COLORCHOOSERWIDGET_H
#define COLORCHOOSERWIDGET_H

// Qt
#include <QWidget>

namespace Ui {
class colorChooserWidget;
}

/**
 * @brief The ColorChooserWidget class is a Qt UI class wich represents
 * a widget with two color chooser buttons.
 */
class ColorChooserWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ColorChooserWidget standard constructor.
     * @param parent Parent widget.
     */
    explicit ColorChooserWidget(QWidget *parent = 0);

    /**
     * @brief ColorChooserWidget destructor.
     */
    ~ColorChooserWidget();

    /**
     * @brief setColors Setter for the two color button's color.
     * @param colors Colors to be set.
     */
    void setColors(std::pair<QColor, QColor> colors);

    /**
     * @brief getColors Getter for the two selected colors.
     * @return Pair of the two selected colors.
     */
    std::pair<QColor, QColor> getColors() const;

private slots:
    /**
     * @brief changePossibleColor Slot that gets connected to the possible color button.
     */
    void changePossibleColor();

    /**
     * @brief changeChosenColor Slot that gets connected to the chosen color button.
     */
    void changeChosenColor();

private:
    Ui::colorChooserWidget *ui;

    /**
     * @brief colors Pair that holds the two color values.
     */
    std::pair<QColor, QColor> colors;
};

#endif // COLORCHOOSERWIDGET_H
