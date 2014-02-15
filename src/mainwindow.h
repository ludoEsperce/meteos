#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QGraphicsView;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent = 0);
private:
    QGraphicsView* m_view;
};

#endif // MAINWINDOW_H
