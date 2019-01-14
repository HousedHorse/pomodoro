#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStyle>
#include "task.h"
#include "actionbutton.h"

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

    void on_action_Start_triggered();

    void on_action_Stop_triggered();

    void on_action_Previous_triggered();

    void on_action_Next_triggered();

    void on_action_Clear_Completed_triggered();

    void on_action_Save_triggered();

    void on_action_New_Worksheet_triggered();

    void on_actionSave_As_triggered();

    void on_action_About_triggered();

    void on_action_Usage_Guide_triggered();

    void slotToggleCompleted(bool completed);

public slots:

private:
    void addTask(Task* t = nullptr, QWidget* w = nullptr);
    void moveTask(Task* t = nullptr,QWidget* d = nullptr);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
