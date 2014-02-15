#include "gamescene.h"
#include <QGraphicsRectItem>

#define BLOCK_WIDTH 80
#define BLOCK_HEIGHT 80

GameScene::GameScene(QObject* parent)
: QGraphicsScene(parent)
{
    
    setSceneRect(0, 0, BLOCK_WIDTH*9, BLOCK_HEIGHT*12);
    for (int y = 0; y < 12; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            QGraphicsRectItem* item = addRect(QRectF(x*BLOCK_WIDTH, y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT), QPen(Qt::black, 1), Qt::red);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        }
    }
}
