#include "mainwindow.h"
#include "gamescene.h"
#include "hud/timer.h"

#include <QLabel>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
{
    m_view = new QGraphicsView(this);
    m_engine = new Engine(this);
    QWidget* centralWidget = new QWidget();

    // dans le layout mettre view et HUD
    QHBoxLayout* hboxLayout = new QHBoxLayout();
    QVBoxLayout* vboxLayout = new QVBoxLayout();

    // HUD 1 score, nb bloc envoyé, timer
    // HUD 2 , avatar player, type de planete/mode
    QPushButton* button1 = new QPushButton("Play");
    QPushButton* button2 = new QPushButton("Stop");
    QPushButton* button3 = new QPushButton("Layout right");
    QLabel *label = new QLabel();
    label->setText("...");


    Timer* timer = new Timer(0, 10000); // 10 secondes
    connect(button1, SIGNAL(clicked()), timer, SLOT(start()));
    connect(button1, SIGNAL(clicked()), m_engine, SLOT(play()));
    connect(button2, SIGNAL(clicked()), timer, SLOT(stop()));
    connect(button2, SIGNAL(clicked()), m_engine, SLOT(stop()));
    //connect(timer, SIGNAL(timeIsOut(QString)), label, SLOT(setText(QString)));

    // left layout
    vboxLayout->addWidget(button1);
    vboxLayout->addWidget(button2);
    vboxLayout->addWidget(label);
    vboxLayout->addWidget(timer);
    vboxLayout->setSpacing(10);

    // main layout
    hboxLayout->addItem(vboxLayout);
    hboxLayout->addWidget(m_view);
    hboxLayout->addWidget(button3);
    centralWidget->setLayout(hboxLayout);
    this->  setCentralWidget(centralWidget);

    GameScene* scene = new GameScene(this);
    m_view->setRenderHint(QPainter::Antialiasing, true);
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setScene(scene);
    m_view->setFixedSize(m_view->sceneRect().width()+10, m_view->sceneRect().height()+10);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_engine, SIGNAL(timeout()), scene, SLOT(next()));
    connect(m_engine, SIGNAL(spawnTimeout()), scene, SLOT(spawnBlock()));
}
