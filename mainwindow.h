#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_Task_triggered();

    void on_action_Quit_triggered();

private:
    void addTask(Task* t);
    Ui::MainWindow *ui;
    QList<Task*> tasks;
};

#endif // MAINWINDOW_H
