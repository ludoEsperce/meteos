#ifndef ENGINE_H
#define ENGINE_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

class Engine : public QObject
{
    Q_OBJECT
public:
    Engine(QObject* parent);
signals:
    void timeout();
    void spawnTimeout();
public slots:
    void play();
    void pause();
    void stop();
private:
    QTimer* timer;
    QTimer* spawnTimer;
};

#endif // ENGINE_H
