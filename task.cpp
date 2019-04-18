#include "task.h"
#include "ui_task.h"
#include <QDebug>
#include <QTime>

Task::Task(QWidget *parent, const QString& name) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);

    // set task name
    m_name = name;

    // set task time to 30 minutes
    // break time at 25 minutes
    m_maxTimeSeconds = 1800;
    m_workTimeCutoff = 1500;
    //m_maxTimeSeconds = 3;
    //m_workTimeCutoff = 2;
    m_currTimeSeconds = 0;

    // set work time and break time
    m_workTime = QTime(0,0,0);
    m_breakTime = QTime(0,0,0);
}

Task::~Task()
{
    delete ui;
}

QString Task::name() const
{
    return m_name;
}

void Task::setName(const QString &name)
{
    m_name = name;
}

void Task::setEnabled(bool enabled)
{
    setWorkBarEnabled(enabled);
    ui->workLabel->setEnabled(enabled);
    ui->breakLabel->setEnabled(enabled);

    // break bar should always be disabled by default
    setBreakBarEnabled(false);
}

void Task::on_lineEdit_textEdited(const QString &arg1)
{
    setName(ui->lineEdit->text());
}

void Task::on_checkBox_toggled(bool checked)
{
    emit toggleCompleted(checked);
}

int Task::workTimeCutoff() const
{
    return m_workTimeCutoff;
}

void Task::setWorkTimeCutoff(int workTimeCutoff)
{
    m_workTimeCutoff = workTimeCutoff;
}

int Task::currTimeSeconds() const
{
    return m_currTimeSeconds;
}

int Task::maxTimeSeconds() const
{
    return m_maxTimeSeconds;
}

void Task::setMaxTimeSeconds(int maxTimeSeconds)
{
    m_maxTimeSeconds = maxTimeSeconds;
}

void Task::incrementTime()
{
    m_currTimeSeconds += 1;

    updateProgressBar();
    updateTimes();

    // work is done
    if(m_currTimeSeconds >= m_workTimeCutoff)
        workDone();

    // work and break are done
    if(m_currTimeSeconds >= m_maxTimeSeconds)
        breakDone();
}

void Task::updateProgressBar()
{
    if(m_currTimeSeconds < m_workTimeCutoff)
    {
        int progress = qRound((float) m_currTimeSeconds / (float) m_workTimeCutoff * 100);
        ui->workBar->setValue(progress);
    }
    else if(m_currTimeSeconds < m_maxTimeSeconds)
    {
        ui->workBar->setValue(100);
        setWorkBarEnabled(false);
        setBreakBarEnabled(true);

        int progress = qRound((float) (m_currTimeSeconds - m_workTimeCutoff) / (float) (m_maxTimeSeconds - m_workTimeCutoff) * 100);
        ui->breakBar->setValue(progress);
    }
    else
    {
        ui->workBar->setValue(100);
        ui->breakBar->setValue(100);
        setWorkBarEnabled(false);
        setBreakBarEnabled(false);
    }
}

void Task::resetProgress()
{
    // reset progress bars
    ui->workBar->setValue(0);
    ui->breakBar->setValue(0);

    // reset time displays
    m_workTime.setHMS(0,0,0);
    m_breakTime.setHMS(0,0,0);
    ui->workTime->setText(m_workTime.toString("mm:ss"));
    ui->breakTime->setText(m_breakTime.toString("mm:ss"));

    // reset which bar is enabled
    setWorkBarEnabled(true);
    setBreakBarEnabled(false);
}

void Task::updateTimes()
{
    if(m_currTimeSeconds < m_workTimeCutoff)
    {
        QTime t = QTime(0,0,0);
        m_workTime = t.addSecs(m_currTimeSeconds);
    }
    else if(m_currTimeSeconds < m_maxTimeSeconds)
    {
        QTime t = QTime(0,0,0);
        m_breakTime = t.addSecs(m_currTimeSeconds - m_workTimeCutoff);
    }
    else
    {
        return;
    }

    ui->workTime->setText(m_workTime.toString("mm:ss"));
    ui->breakTime->setText(m_breakTime.toString("mm:ss"));
}

void Task::setWorkBarEnabled(bool enabled)
{
    ui->workBar->setEnabled(enabled);
    ui->workTime->setEnabled(enabled);
}

void Task::setBreakBarEnabled(bool enabled)
{
    ui->breakBar->setEnabled(enabled);
    ui->breakTime->setEnabled(enabled);
}

void Task::workDone()
{
    emit signalWorkDone();
}

void Task::breakDone()
{
    emit signalBreakDone();
    emit done();
}

void Task::reset()
{
    m_currTimeSeconds = 0;
    resetProgress();
}
