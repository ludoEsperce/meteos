#include "gamescene.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneEvent>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <cmath>
#include <QtCore/QPropertyAnimation>

#include "block.h"

static qint64 t0 = 0;

const int GameScene::rowCount = 12;
const int GameScene::columnCount = 9;

static int randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

GameScene::GameScene(QObject* parent)
: QGraphicsScene(parent), m_moveBlockActivated(false), m_movedBlock(0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    setSceneRect(0, 0, Block::defaultWidth*columnCount, Block::defaultHeight*rowCount);
    for (int i = columnCount; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
//             int r = randInt(0, 3);
            int r = qrand() % 4;
            Block* block = new Block(i, j, static_cast<Block::Color>(r));
            addBlock(block);
        }
    }
    
//     QTimer::singleShot(1000, this, SLOT(check()));
    check();
}

void GameScene::check()
{
    foreach(Block* block, m_blocks)
    {
        while (!horizontalAlignedBlock(block).isEmpty() || checkVerticalAlignedBlock(block))
            block->nextColor();
    }
    
    t0 = QDateTime::currentMSecsSinceEpoch();
//     m_blocks.first()->setState(Block::MoveUp);
//     startTimer(17);
    
}

void GameScene::addBlock(Block* block)
{
    if (!block)
        return;
    
    m_blocks << block;
    addItem(block);
    
}

void GameScene::spawnBlock()
{
    int c = qrand() % columnCount;
    int r = qrand() % 4;
    Block* block = new Block(0, c, static_cast<Block::Color>(r));
    addBlock(block);
    
    block->setState(Block::MoveDown);
    
//     int r = 0;
//     for (; r < rowCount; r++)
//     {
//         if (blockAt(r, c))
//             break;
//     }
//     
//     block->setCell(r, c);
}

Block* GameScene::blockAt(int row, int column)
{
    QGraphicsItem* item = itemAt((qreal)column*Block::defaultWidth+1, (qreal)row*Block::defaultHeight+1, QTransform());
    return qgraphicsitem_cast<Block*>(item);
}

Block* GameScene::blockAt(const QPointF& pos)
{
    QGraphicsItem* item = itemAt(pos, QTransform());
    return qgraphicsitem_cast<Block*>(item);
}

int GameScene::rowFromPos(const QPointF& pos)
{
    return floor(pos.y() / Block::defaultHeight);
}

int GameScene::columnFromPos(const QPointF& pos)
{
    return floor(pos.x() / Block::defaultWidth);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "pos: " << event->scenePos();
    qDebug() << "row: " << rowFromPos(event->scenePos());
    qDebug() << "col: " << columnFromPos(event->scenePos());
    if ((m_movedBlock = blockAt(event->scenePos())))
    {
        qDebug() << "move block activated";
        m_moveBlockActivated = true;
    }
    
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_moveBlockActivated = false;
    m_movedBlock = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
//     qDebug() << "pos: " << event->scenePos();
//     Block* block = blockAt(event->scenePos());
    if (m_movedBlock && m_moveBlockActivated)
    {
        int row = rowFromPos(event->scenePos());
        int col = columnFromPos(event->scenePos());
        if (row != m_movedBlock->row())
        {
            Block* oldBlock = blockAt(row, m_movedBlock->column());
            if (!oldBlock)
                return;
            qDebug() << "new pos: " << row << " " << m_movedBlock->column();
            qDebug() << "old pos: " << m_movedBlock->row() << " " << m_movedBlock->column();
            oldBlock->setCell(m_movedBlock->row(), m_movedBlock->column());
            m_movedBlock->setCell(row, m_movedBlock->column());
            int count = 0;
            QList<Block*> items;
            if (!(items = horizontalAlignedBlock(m_movedBlock)).isEmpty())
                qDebug() << "H Aligned with moved block " << items.size();
            buildGroup(items);
                
            if (!(items = horizontalAlignedBlock(oldBlock)).isEmpty())
                qDebug() << "H Aligned with old block " << items.size();
            
            
            // Je recherche les block du dessus et les ajoute au groupe
            
            if (checkVerticalAlignedBlock(m_movedBlock, &count))
                qDebug() << "V Aligned with moved block " << count;
                
            if (checkVerticalAlignedBlock(oldBlock, &count))
                qDebug() << "V Aligned with old block " << count;
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

QList<Block*> GameScene::horizontalAlignedBlock(Block* block)
{
    int c = 1;
    QList<Block*> items;
    items << block;
    for (int i = 1; i <= 2; i++)
    {
        Block* leftBlock = blockAt(block->row(), block->column()-i);
        if (leftBlock && leftBlock->color() == block->color())
            items << leftBlock;
        else
            break;
    }
    
    for (int i = 1; i <= 2; i++)
    {
        Block* rightBlock = blockAt(block->row(), block->column()+i);
        if (rightBlock && rightBlock->color() == block->color())
            items << rightBlock;
        else
            break;
    }

    return (items.size() >= 3) ? items : QList<Block*>();
}

bool GameScene::checkVerticalAlignedBlock(Block* block, int* count)
{
    int c = 1;
    for (int i = 1; i <= 2; i++)
    {
        Block* topBlock = blockAt(block->row()-i, block->column());
        if (topBlock && topBlock->color() == block->color())
        {
            qDebug() << "top++";
            c++;
        }
        else
            break;
    }
    
    for (int i = 1; i <= 2; i++)
    {
        Block* bottomBlock = blockAt(block->row()+i, block->column());
        if (bottomBlock && bottomBlock->color() == block->color())
        {
            qDebug() << "bot++";
            c++;
        }
        else
            break;
    }
    
    if (count)
        *count = c;

    return (c >= 3);
}

QGraphicsItemGroup* GameScene::buildGroup(const QList< Block* >& blocks)
{
//     QGraphicsItemGroup* group = new QGraphicsItemGroup;
    foreach(Block* b, blocks)
    {
        int row = b->row();
        //group->addToGroup(b);
        b->setState(Block::MoveUp);
        while(row > 0)
        {
            Block* blockOnTop = blockAt(row, b->column());
            if (blockOnTop && blockOnTop->state() == Block::NoMove)
            {
                //group->addToGroup(blockOnTop);
                blockOnTop->setState(Block::MoveUp);
            }
            row--;
        }
    }
}

// void GameScene::timerEvent(QTimerEvent* event)
// {
//     advance();
//     
// //     qint64 t = QDateTime::currentMSecsSinceEpoch();
// //     qint64 dt = t - t0;
// //     t0 = t;
// //     
// // //     qDebug() << "dt:" << dt;
// //     
// //     m_blocks.first()->update(dt);
//     
//     QObject::timerEvent(event);
// }

void GameScene::next()
{
    advance();
    
    foreach(Block* b, m_blocks)
    {
        if (b->state() == Block::MoveDown)
        {
            QList<QGraphicsItem*> items = b->collidingItems(Qt::IntersectsItemBoundingRect);
            if (!items.isEmpty())
            {
                b->setState(((Block*)items.first())->state());
                qreal y = -1;
                foreach(QGraphicsItem* item, items)
                {
                    Block* block = (Block*) item;
                    if (b->column() == block->column())
                        y = block->y() - Block::defaultHeight;
                }
                if (y != -1)
                    b->setPos(b->column()*Block::defaultWidth, y);
            } else if(b->y() > (rowCount-1)*Block::defaultHeight){
                b->setCell(rowCount-1, b->column());
                b->setState(Block::NoMove);
            }
        }
        
    }
}
