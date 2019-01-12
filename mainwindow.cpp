#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Task_triggered()
{
    Task* task = new Task(this);

    addTask(task);
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::addTask(Task *t)
{
    if(t == nullptr)
        return;

    tasks.push_back(t);

    // show status bar message
    statusBar()->showMessage("Task added", 2000);
}
