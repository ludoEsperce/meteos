#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>
#include <QObject>

class Block : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    enum {
        Type = UserType + 1
    };
    enum Color {
        Color1,
        Color2,
        Color3,
        Color4,
        Color5
    };
    
    Block(QGraphicsItem* parent = 0);
    Block(int row, int column, QGraphicsItem* parent = 0);
    Block(int row, int column, Color color, QGraphicsItem* parent = 0);
    void setCell(int row, int column);
    int row() const { return m_row; }
    int column() const { return m_column; }
    Color color() const { return m_color; }
    void setColor(Color color);
    void nextColor();
    virtual int type() const { return Type; }
    
    void update(qint64 dt);
    
    static int defaultWidth;
    static int defaultHeight;
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
//     virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
//     virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
//     virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
    void init();
    int rowFromPos(const QPoint& pos);
    int columnFromPos(const QPoint& pos);
    void updateColor();
private:
    int m_row;
    int m_column;
    int m_n;
    Color m_color;
    double m_weight;
    double m_speed;
    double m_maxSpeed;
    double m_acceleration;
};

#endif // BLOCK_H
