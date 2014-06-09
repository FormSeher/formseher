#ifndef LINELISTWIDGET_H
#define LINELISTWIDGET_H

#include <QColor>
#include <QPushButton>
#include <QWidget>
#include <QListWidgetItem>
#include "line.h"

namespace Ui {
class LineListWidget;
}

class LineListWidget : public QWidget
{
    Q_OBJECT

signals:
    void itemSelected(int);
    void myItemDoubleClicked(int);

public slots:
    void passItemSelected(int);
    void passItemDoubleClicked();

public:
    explicit LineListWidget(QWidget *parent = 0);
    ~LineListWidget();

    void setLineList(std::vector<formseher::Line> lines);
    void clearLineList() const;

private:
    Ui::LineListWidget *ui;

    std::vector<formseher::Line> lines;
};
#endif // LINELISTWIDGET_H
