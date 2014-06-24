#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "line.h"
#include "imagemode.h"

#include <QWidget>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

public slots:
    void slot_configurationChanged();
    void slot_repaint(cv::Mat image);
    void slot_setLines(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line> > lines);
    void slot_doubleClicked();

signals:
    void signal_configurationChanged(ImageMode, int, int);
    void signal_lineDoubleClicked(std::pair<int, int>);


private:
    Ui::ImageWidget *ui;
};

#endif // IMAGEWIDGET_H
