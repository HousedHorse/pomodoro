#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QTime>

class MainWindow;

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr, const QString& name = "");
    ~Task();

    QString name() const;
    void setName(const QString &name);
    void setEnabled(bool enabled = true);

    void incrementTime();

    void reset();

    int maxTimeSeconds() const;
    void setMaxTimeSeconds(int maxTimeSeconds);

    int currTimeSeconds() const;

    int workTimeCutoff() const;
    void setWorkTimeCutoff(int workTimeCutoff);

signals:
    void toggleCompleted(bool);
    void done();
    void signalWorkDone();
    void signalBreakDone();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_checkBox_toggled(bool checked);

private:
    Ui::Task *ui;
    QString m_name;
    int m_maxTimeSeconds;
    int m_workTimeCutoff;
    int m_currTimeSeconds;

    QTime m_workTime;
    QTime m_breakTime;

    void updateProgressBar();
    void resetProgress();
    void updateTimes();

    void setWorkBarEnabled(bool enabled);
    void setBreakBarEnabled(bool enabled);

    void workDone();
    void breakDone();
};

#endif // TASK_H
