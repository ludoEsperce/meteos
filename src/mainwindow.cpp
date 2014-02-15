#include "mainwindow.h"
#include "gamescene.h"

#include <QLabel>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
{
    m_view = new QGraphicsView(this);
    GameScene* scene = new GameScene(this);
    m_view->setRenderHint(QPainter::Antialiasing, true);
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setScene(scene);
    m_view->setFixedSize(m_view->sceneRect().width()+10, m_view->sceneRect().height()+10);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(m_view);
}
