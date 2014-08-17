#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "engine.h"
class QGraphicsView;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = 0);
private:
    QGraphicsView* m_view;
    Engine* m_engine;
};

#endif // MAINWINDOW_H
