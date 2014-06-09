#include "linelistwidget.h"
#include "ui_linelistwidget.h"

#include <iostream>

LineListWidget::LineListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineListWidget)
{
    ui->setupUi(this);
    connect(ui->lineListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(passItemSelected(int)));
    connect(ui->lineListWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(passItemDoubleClicked()));
}

LineListWidget::~LineListWidget()
{
    delete ui;
}

void LineListWidget::setLineList(std::vector<formseher::Line> lines)
{
    this->lines = lines;
    ui->lineListWidget->clear();
    for(auto line : lines)
    {
        std::stringstream listtext;
        listtext << "Line " << line.getStart() << " → " << line.getEnd();
        ui->lineListWidget->addItem(new QListWidgetItem(tr(listtext.str().c_str())));
    }
}

void LineListWidget::passItemSelected(int i)
{
    emit itemSelected(i);
}

void LineListWidget::passItemDoubleClicked()
{
    emit myItemDoubleClicked(ui->lineListWidget->currentRow());
}

void LineListWidget::clearLineList() const
{
    ui->lineListWidget->clear();
}
