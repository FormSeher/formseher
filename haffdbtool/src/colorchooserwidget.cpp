#include "include/colorchooserwidget.h"
#include "ui_colorchooserwidget.h"

#include <QColorDialog>

ColorChooserWidget::ColorChooserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorChooserWidget)
{
    ui->setupUi(this);

    connect(ui->defaultColorButton, SIGNAL(clicked()), this, SLOT(changeDefaultColor()));
    connect(ui->selectedColorButton, SIGNAL(clicked()), this, SLOT(changeSelectedColor()));
}

ColorChooserWidget::~ColorChooserWidget()
{
    delete ui;
}

void ColorChooserWidget::changeDefaultColor()
{
    QColor color = QColorDialog::getColor(defaultColor, this);
       if (color.isValid())
       {
           defaultColor = color;
       }
       updateColorButtons();

}

void ColorChooserWidget::changeSelectedColor()
{
    QColor color = QColorDialog::getColor(selectedColor, this);
       if (color.isValid())
       {
           selectedColor = color;
       }
       updateColorButtons();
}

void ColorChooserWidget::setDefaultColor(QColor color)
{
    defaultColor = color;
    emit updateColorButtons();
}

void ColorChooserWidget::setSelectedColor(QColor color)
{
    selectedColor = color;
    updateColorButtons();
}

void ColorChooserWidget::updateColorButtons()
{
    // Default Color Button
    ui->defaultColorButton->setText(defaultColor.name());
    ui->defaultColorButton->setPalette(QPalette(defaultColor));
    ui->defaultColorButton->setAutoFillBackground(true);

    // Selected Color Button
    ui->selectedColorButton->setText(selectedColor.name());
    ui->selectedColorButton->setPalette(QPalette(selectedColor));
    ui->selectedColorButton->setAutoFillBackground(true);

    emit colorUpdated();
}


QColor ColorChooserWidget::getDefaultColor() const
{
    return defaultColor;
}

QColor ColorChooserWidget::getSelectedColor() const
{
    return selectedColor;
}
