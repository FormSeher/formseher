#include "algorithmcontrolwidget.h"
#include "ui_algorithmcontrolwidget.h"

AlgorithmControlWidget::AlgorithmControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmControlWidget)
{
    ui->setupUi(this);
}

AlgorithmControlWidget::~AlgorithmControlWidget()
{
    delete ui;
}
