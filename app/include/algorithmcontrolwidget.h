#ifndef ALGORITHMCONTROLWIDGET_H
#define ALGORITHMCONTROLWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>

namespace Ui {
class AlgorithmControlWidget;
}

class AlgorithmControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlgorithmControlWidget(QWidget *parent = 0);
    ~AlgorithmControlWidget();

    void setCvMatrix(cv::InputArray matrix);

private:
    Ui::AlgorithmControlWidget *ui;
};

#endif // ALGORITHMCONTROLWIDGET_H
