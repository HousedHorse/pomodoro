#ifndef TASK_H
#define TASK_H

#include <QWidget>
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

signals:
    void toggleCompleted(bool);

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_checkBox_toggled(bool checked);

private:
    Ui::Task *ui;
    QString m_name;
};

#endif // TASK_H
