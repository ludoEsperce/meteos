#ifndef BLOCK_H
#define BLOCK_H

#include <qgraphicsitem.h>

class Block : public QGraphicsRectItem
{
public:
    Block(QGraphicsItem* parent, QGraphicsScene* scene);
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event);
};

#endif // BLOCK_H
