#ifndef ALGORITHMCONTROLWIDGET_H
#define ALGORITHMCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class AlgorithmControlWidget;
}

class AlgorithmControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmControlWidget(QWidget *parent = 0);
    ~AlgorithmControlWidget();

private:
    Ui::AlgorithmControlWidget *ui;
};

#endif // ALGORITHMCONTROLWIDGET_H
