#ifndef COLORCHOOSERWIDGET_H
#define COLORCHOOSERWIDGET_H

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

    void setDefaultColor(QColor color);
    void setSelectedColor(QColor color);
    QColor getDefaultColor() const;
    QColor getSelectedColor() const;

signals:
    void colorUpdated();

private slots:
    void changeDefaultColor();
    void changeSelectedColor();

private:
    Ui::colorChooserWidget *ui;

    QColor defaultColor = QColor();
    QColor selectedColor = QColor();

    void updateColorButtons();
};

#endif // COLORCHOOSERWIDGET_H
