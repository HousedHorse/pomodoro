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

    // show status bar message
    statusBar()->showMessage("Task created", 2000);
}

void MainWindow::on_action_Quit_triggered()
{
    close();
}

void MainWindow::addTask(Task *t, QListWidget* w)
{
    if(t == nullptr)
        return;
    if(w == nullptr)
        w = ui->inProgress;

    // add to widget
    QListWidgetItem* item;
    item = new QListWidgetItem(w);
    w->addItem(item);
    item->setSizeHint(t->sizeHint());
    w->setItemWidget(item,t);

    // set timer enabled if appropriate
    if(w->count() == 1) {
        t->setEnabled(true);
    }
}
