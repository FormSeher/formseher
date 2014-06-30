#ifndef COLORCHOOSERWIDGET_H
#define COLORCHOOSERWIDGET_H

// Qt
#include <QWidget>

namespace Ui {
class colorChooserWidget;
}

class ColorChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorChooserWidget(QWidget *parent = 0);
    ~ColorChooserWidget();

    void setColors(std::pair<QColor, QColor> colors);

    std::pair<QColor, QColor> getColors() const;

private slots:
    void changePossibleColor();
    void changeChosenColor();

private:
    Ui::colorChooserWidget *ui;

    std::pair<QColor, QColor> colors;
};

#endif // COLORCHOOSERWIDGET_H
