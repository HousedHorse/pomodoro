#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add toolbar toggle to view menu
    QAction* toggleToolbar = ui->mainToolBar->toggleViewAction();
    toggleToolbar->setText("&Toolbar");
    ui->menu_View->addAction(toggleToolbar);

    // set size for inProgress section
    Task* temp = new Task;
    ui->inProgress->setMaximumHeight(temp->geometry().height());
    delete(temp);

    // set icons for media actions
    ui->action_Start->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->action_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->action_Previous->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->action_Next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    // connect actions to action buttons
    ui->playPauseButton->setAction(ui->action_Start);
    ui->prevButton->setAction(ui->action_Previous);
    ui->nextButton->setAction(ui->action_Next);
    ui->clearButton->setAction(ui->action_Clear_Completed);
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
    if(w == ui->inProgress && ui->inProgress->count() >= 1)
        w = ui->upNext;

    // add to widget
    QListWidgetItem* item;
    item = new QListWidgetItem(w);
    w->addItem(item);
    item->setSizeHint(t->sizeHint());
    t->setItem(item);
    w->setItemWidget(item,t);

    // connect item checkbox to changing completion
    connect(t, SIGNAL(toggleCompleted(bool)), this, SLOT(toggleCompleted(bool)));

    // set timer enabled if appropriate
    if(w == ui->inProgress) {
        t->setEnabled(true);
    }
}

void MainWindow::on_action_Start_triggered()
{
    // toggle between start and stop actions in UI
    ui->action_Start->setEnabled(false);
    ui->action_Stop->setEnabled(true);
    ui->playPauseButton->setAction(ui->action_Stop);

    // FIXME: implement timer starting
}

void MainWindow::on_action_Stop_triggered()
{
    // toggle between start and stop actions in UI
    ui->action_Start->setEnabled(true);
    ui->action_Stop->setEnabled(false);
    ui->playPauseButton->setAction(ui->action_Start);

    // FIXME: implement timer stopping
}

void MainWindow::on_action_Previous_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_Next_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_Clear_Completed_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_Save_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_New_Worksheet_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_actionSave_As_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_About_triggered()
{

    // FIXME: implement this

}

void MainWindow::on_action_Usage_Guide_triggered()
{

    // FIXME: implement this

}

void MainWindow::toggleCompleted(bool completed)
{
    Task* t = qobject_cast<Task*>(sender());
    QListWidgetItem *item = t->item();
    if(completed){
        qDebug() << ui->inProgress->takeItem(ui->inProgress->row(item));
        qDebug() << ui->upNext->takeItem(ui->upNext->row(item));
        ui->done->insertItem(ui->done->count(), item);
        ui->done->setItemWidget(item,t); // causing the crash
    } else {
        ui->done->takeItem(ui->done->row(item));
        ui->upNext->addItem(item);
    }
}
