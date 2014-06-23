#ifndef MYPOINT_H
#define MYPOINT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtCore>

class myPoint : public QGraphicsItem
{
public:
    myPoint(QPoint point);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPoint point;
    QPoint recPoint;
    qreal large = 7;
    qreal small = 3;
    qreal size = small;
    bool pressed;
    bool hovered;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void makeLargeRec();
    void makeSmallRec();
    void recalcRec();

};

#endif // MYPOINT_H
