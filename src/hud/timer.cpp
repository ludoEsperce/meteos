#include "timer.h"

Timer::Timer(int startValue, int endValue) {
    m_lcdNumber = new QLCDNumber(this);
    m_timer = new QTimeLine(startValue < endValue ? endValue - startValue : startValue - endValue) ;
    m_timer->setFrameRange(startValue,endValue);
    m_startValue = startValue;
    m_endValue = endValue;
    m_currentValue = startValue;
    update(startValue);
    connect(m_timer, SIGNAL(frameChanged(int)), this, SLOT(update(int)));
    this->setFixedWidth(100);
}

void Timer::update(int frame) {
    qDebug() << "...-> " << frame;
    m_currentValue = frame;
    m_lcdNumber->display(frame);
}


void Timer::start() {
        m_timer->start();
}

void Timer::stop() {
        m_timer->stop();
}

int Timer::getCurrentValue() {
    return m_currentValue;
}
