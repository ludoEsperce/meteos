#include "engine.h"

Engine::Engine(QObject* parent)
: QObject(parent)
{
    timer = new QTimer(this);
    spawnTimer = new QTimer(this);
    timer->setInterval(33);
    spawnTimer->setInterval(1000);
    
    connect(timer, SIGNAL(timeout()), SIGNAL(timeout()));
    connect(spawnTimer, SIGNAL(timeout()), SIGNAL(spawnTimeout()));
}

void Engine::play()
{
    timer->start();
    spawnTimer->start();
}

void Engine::stop()
{
    timer->stop();
    spawnTimer->stop();
}

void Engine::pause()
{
    stop();
}
