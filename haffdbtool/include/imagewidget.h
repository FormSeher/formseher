#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include "line.h"

#define MODE_IMG "Original"
#define MODE_GREY "Greyscale"
#define MODE_LINES "Lines"
#define MODE_GREY_LINES "Greyscale / Lines"
#define MODE_IMG_LINES "Original / Lines"

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

    void setImage(QString imagePath, cv::Mat& image);
    void repaintImage(std::vector<formseher::Line> selectedLines, formseher::Line selectedLine,
                      QColor defaultColor, QColor selectedColor);

signals:
    void imageChanged();
    void imageModeChanged();

private slots:
    void imageChangedActions();

private:
    Ui::ImageWidget *ui;

    cv::Mat originalImage;
    cv::Mat greyImage;
    cv::Mat paintingImage;

    void setImageToLabel();

};

#endif // IMAGEWIDGET_H
