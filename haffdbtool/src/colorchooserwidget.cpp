#include "colorchooserwidget.h"
#include "ui_colorchooserwidget.h"

#include <QColor>
#include <QColorDialog>

ColorChooserWidget::ColorChooserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorChooserWidget)
{
    ui->setupUi(this);

    this->colors.first = Qt::magenta;
    this->colors.second = Qt::green;

    ui->buttonPossibleColor->setText(this->colors.first.name());
    ui->buttonPossibleColor->setPalette(QPalette(this->colors.first));
    ui->buttonPossibleColor->setAutoFillBackground(true);
    ui->buttonChosenColor->setText(this->colors.second.name());
    ui->buttonChosenColor->setPalette(QPalette(this->colors.second));
    ui->buttonChosenColor->setAutoFillBackground(true);

    connect(ui->buttonPossibleColor, SIGNAL(clicked()), this, SLOT(changePossibleColor()));
    connect(ui->buttonChosenColor, SIGNAL(clicked()), this, SLOT(changeChosenColor()));
}

ColorChooserWidget::~ColorChooserWidget()
{
    delete ui;
}

void ColorChooserWidget::changePossibleColor()
{
    QColor color = QColorDialog::getColor(this->colors.first, this);
    if (color.isValid())
    {
        this->colors.first = color;
        ui->buttonPossibleColor->setText(this->colors.first.name());
        ui->buttonPossibleColor->setPalette(QPalette(this->colors.first));
        ui->buttonPossibleColor->setAutoFillBackground(true);
    }
}

void ColorChooserWidget::changeChosenColor()
{
    QColor color = QColorDialog::getColor(this->colors.second, this);
    if (color.isValid())
    {
        this->colors.second = color;
        ui->buttonChosenColor->setText(this->colors.second.name());
        ui->buttonChosenColor->setPalette(QPalette(this->colors.second));
        ui->buttonChosenColor->setAutoFillBackground(true);
    }
}

std::pair<QColor, QColor> ColorChooserWidget::getColors() const
{
    return this->colors;
}

void ColorChooserWidget::setColors(std::pair<QColor, QColor> colors)
{
    this->colors = colors;
}
