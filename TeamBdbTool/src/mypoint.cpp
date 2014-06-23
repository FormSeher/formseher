#include "mypoint.h"

myPoint::myPoint(QPoint point)
{
    pressed = false;
    hovered = false;
    point;

    // set flags
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF myPoint::boundingRect() const
{
    return QRectF(recPoint, QSizeF(size,size));
}

void myPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush = QBrush(Qt::black);

    if (hovered)
    {
     brush.setColor(Qt::yellow);
    }

    if (pressed)
    {
     brush.setColor(Qt::red);
    }

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void myPoint::makeLargeRec()
{
    size = large;
    recalcRec();
}

void myPoint::makeSmallRec()
{
    size = small;
    recalcRec();
}

void myPoint::recalcRec()
{
    recPoint = point - QPoint(size/2,size/2);
}

void myPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    makeLargeRec();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void myPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    makeSmallRec();
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void myPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hovered = true;
    makeLargeRec();
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void myPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hovered = false;
    makeSmallRec();
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}


