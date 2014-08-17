#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QLCDNumber>
#include <QTimeLine>
#include <QString>
#include <QDebug>

class Timer : public QWidget
{
    Q_OBJECT

    public:
        Timer(int startValue, int endValue);
        int getCurrentValue();

    private slots:
        void update(int a);

    public slots:
        void start();
        void stop();

    private:
        QLCDNumber *m_lcdNumber;
        QTimeLine *m_timer;
        int m_currentValue;
        int m_startValue;
        int m_endValue;
        void updateDisplay();

    signals:
        void timeIsOut();
        void timeIsOut(QString mess);

};

#endif // TIMER_H
