#include "block.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsSceneEvent>
#include <QBrush>
#include <QPen>
#include <qpainter.h>
#include <QtCore/QDebug>

int Block::defaultWidth = 40;
int Block::defaultHeight = 40;

Block::Block(QGraphicsItem* parent)
: QObject()
, QGraphicsRectItem(parent)
, m_row(0)
, m_column(0)
{
    init();
}

Block::Block(int row, int column, QGraphicsItem* parent)
: QGraphicsRectItem(parent)
, m_row(row)
, m_column(column)
{
    init();
}

Block::Block(int row, int column, Block::Color color, QGraphicsItem* parent)
: QGraphicsRectItem(parent)
, m_row(row)
, m_column(column)
, m_color(color)
{
    init();
    updateColor();
}

void Block::init()
{
    setFlags(/*QGraphicsItem::ItemIsMovable | */QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    setBrush(QBrush(Qt::red));
    setPen(QPen(Qt::black, 2));
    setRect(0, 0, defaultWidth, defaultHeight);
    setCell(m_row, m_column);
    static int n = 0;
    m_n = ++n;
    m_acceleration = 0.2;
    m_speed = 0;
    m_maxSpeed = 500;
    m_weight = 1;
}

void Block::setColor(Block::Color color)
{
    if (m_color == color)
        return;
    
    m_color = color;
    updateColor();
}

void Block::updateColor()
{
    QColor qColor;
    switch(m_color)
    {
        case Color1:
            qColor = Qt::red;
            break;
        case Color2:
            qColor = Qt::green;
            break;
        case Color3:
            qColor = Qt::yellow;
            break;
        case Color4:
            qColor = Qt::magenta;
            break;
        case Color5:
            qColor = Qt::blue;
            break;
    }
    setBrush(qColor.lighter(80));
}

void Block::setCell(int row, int column)
{
    m_row = row;
    m_column = column;
    QGraphicsItem::setPos(column*Block::defaultHeight, row*Block::defaultWidth);
}

int Block::rowFromPos(const QPoint& pos)
{
    
}

int Block::columnFromPos(const QPoint& pos)
{
    
}

void Block::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
//     qDebug() << "leave";
    setPen(QPen(Qt::green, 2));
    setBrush(brush().color().lighter(60));
    setZValue(1000);
}

void Block::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
//     qDebug() << "leave";
    setPen(QPen(Qt::black, 2));
    setBrush(brush().color().darker(60));
    setZValue(1);
}

// void Block::mousePressEvent(QGraphicsSceneMouseEvent* event)
// {
//     qDebug() << event->pos();
//     QGraphicsRectItem::mousePressEvent(event);
// }
// 
// void Block::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
// {
//     qDebug() << event->pos();
//     QGraphicsRectItem::mouseMoveEvent(event);
// }
// 
// void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
// {
//     qDebug() << event->pos();
//     QGraphicsRectItem::mouseReleaseEvent(event);
// }

void Block::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    qDebug() << "wheel";
}

void Block::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    QFontMetrics fm = painter->fontMetrics();
    QString text = QString("%1").arg(m_n);
    int fh = fm.height();
    int fw = fm.width(text);
    painter->drawText(QPointF(defaultWidth/2 - fw/2, defaultHeight/2 + fh/2), QString("%1").arg(m_n));
}

void Block::nextColor()
{
    setColor(static_cast<Color>((static_cast<int>(m_color) + 1) % 4));
}

static double a = 0;
static bool forward = true;

void Block::update(qint64 dt)
{
//     a += 0.01;
    if (y() <= 0)
    {
        setY(0);
        return;
    }
    
    if (!forward && y() >= 450)
    {
        setY(450);
        return;
    }
    
    if (y() <= 100)
    {
        forward = false;
        m_speed = 50;
    }
    
    if (forward)
    {
        if (a > 1)
            a = 1;
        else
            a += 0.01;
        m_speed = m_acceleration * dt * (a*a) + m_speed;
        if (m_speed > m_maxSpeed)
            m_speed = m_maxSpeed;
        
        double dy = m_speed / (1000 / dt);
        
        qDebug() << "speed:" << m_speed;
        qDebug() << "y:" << pos().y();
        
        moveBy(0, -dy);
    }
    else
    {
        double dy = m_speed / (1000 / dt);
        
        qDebug() << "speed:" << m_speed;
        qDebug() << "y:" << pos().y();
        
        moveBy(0, dy);
    }
}
