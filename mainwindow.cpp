#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    // set icons for media buttons
    ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

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
    w->setItemWidget(item,t);

    // set timer enabled if appropriate
    if(w == ui->inProgress) {
        t->setEnabled(true);
    }
}

void MainWindow::on_action_Show_Toolbar_toggled(bool arg1)
{

}
