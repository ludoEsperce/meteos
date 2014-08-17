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

GameScene::GameScene(QObject* parent)
: QGraphicsScene(parent), m_moveBlockActivated(false), m_movedBlock(0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    setSceneRect(0, 0, Block::defaultWidth*9, Block::defaultHeight*12);
    for (int i = 9; i < 12; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int r = (qrand() % 4);
            Block* block = new Block(i, j, static_cast<Block::Color>(r));
            addBlock(block);
        }
    }
    
    QTimer::singleShot(1000, this, SLOT(check()));
}

void GameScene::check()
{
    foreach(Block* block, m_blocks)
    {
        while (checkHorizontalAlignedBlock(block) || checkVerticalAlignedBlock(block))
            block->nextColor();
    }
    
    t0 = QDateTime::currentMSecsSinceEpoch();
    startTimer(17);
}

void GameScene::addBlock(Block* block)
{
    if (!block)
        return;
    
    m_blocks << block;
    addItem(block);
    
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
            qDebug() << "new pos: " << row << " " << m_movedBlock->column();
            qDebug() << "old pos: " << m_movedBlock->row() << " " << m_movedBlock->column();
            oldBlock->setCell(m_movedBlock->row(), m_movedBlock->column());
            m_movedBlock->setCell(row, m_movedBlock->column());
            int count = 0;
            if (checkHorizontalAlignedBlock(m_movedBlock, &count))
                qDebug() << "H Aligned with moved block " << count;
                
            if (checkHorizontalAlignedBlock(oldBlock, &count))
                qDebug() << "H Aligned with old block " << count;
            
            if (checkVerticalAlignedBlock(m_movedBlock, &count))
                qDebug() << "V Aligned with moved block " << count;
                
            if (checkVerticalAlignedBlock(oldBlock, &count))
                qDebug() << "V Aligned with old block " << count;
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

bool GameScene::checkHorizontalAlignedBlock(Block* block, int* count)
{
    int c = 1;
    for (int i = 1; i <= 2; i++)
    {
        Block* leftBlock = blockAt(block->row(), block->column()-i);
        if (leftBlock && leftBlock->color() == block->color())
            c++;
        else
            break;
    }
    
    for (int i = 1; i <= 2; i++)
    {
        Block* rightBlock = blockAt(block->row(), block->column()+i);
        if (rightBlock && rightBlock->color() == block->color())
            c++;
        else
            break;
    }
    
    if (count)
        *count = c;
    if (c >= 3)
        return true;
    return false;
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
    if (c >= 3)
        return true;
    return false;
}

void GameScene::timerEvent(QTimerEvent* event)
{
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    qint64 dt = t - t0;
    t0 = t;
    
//     qDebug() << "dt:" << dt;
    
    m_blocks.first()->update(dt);
    
    QObject::timerEvent(event);
}
