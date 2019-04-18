#ifndef TIMERCONTROL_H
#define TIMERCONTROL_H

#include <QObject>

class TimerControl : public QObject
{
    Q_OBJECT
public:
    explicit TimerControl(QObject *parent = nullptr);

signals:
    void incrementTimers();

public slots:
    void toggleTimer(const bool &switchOn);
    void launch();
    void tick();

private:
    bool m_timerOn;
};

#endif // TIMERCONTROL_H
