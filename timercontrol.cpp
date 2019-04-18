#include "timercontrol.h"

#include <QTimer>
#include <QDebug>

TimerControl::TimerControl(QObject *parent) : QObject(parent)
{
    m_timerOn = false;
}

void TimerControl::toggleTimer(const bool &switchOn)
{
    m_timerOn = switchOn;
}

void TimerControl::launch()
{
    QTimer *timer = new QTimer(this);

    timer->start(1000);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(tick()));
}

void TimerControl::tick()
{
    // increment timers if the timers are on
    if(m_timerOn)
        emit incrementTimers();
}
