#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class Block;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject* parent = 0);
    
    int rowFromPos(const QPointF& pos);
    int columnFromPos(const QPointF& pos);
    Block* blockAt(int row, int column);
    Block* blockAt(const QPointF& pos);
    void addBlock(Block* block);
    
    const static int rowCount;
    const static int columnCount;
public slots:
    void spawnBlock();
    void next();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
//     virtual void timerEvent(QTimerEvent* event);
private slots:
    void check();
private:
    QList<Block*> horizontalAlignedBlock(Block* block);
    bool checkVerticalAlignedBlock(Block* block, int* count = 0);
    QGraphicsItemGroup* buildGroup(const QList< Block* >& blocks); 
private:
    bool m_moveBlockActivated;
    Block* m_movedBlock;
    QList<Block*> m_blocks;
};

#endif // GAMESCENE_H
