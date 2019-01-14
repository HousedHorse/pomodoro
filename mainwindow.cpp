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

    QVBoxLayout* l1 = new QVBoxLayout(ui->inProgress);
    QVBoxLayout* l2 = new QVBoxLayout(ui->complete);
    QVBoxLayout* l3 = new QVBoxLayout(ui->upNext);

    l1->setAlignment(Qt::AlignTop);
    l2->setAlignment(Qt::AlignTop);
    l3->setAlignment(Qt::AlignTop);

    // set size for inProgress section
    Task* temp = new Task;
    ui->inProgress->setMinimumHeight(temp->geometry().height() + 32);
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

void MainWindow::addTask(Task *t, QWidget* w)
{
    if(!t)
        return;
    if(!w)
        w = ui->inProgress;
    if(w == ui->inProgress && w->children().count() > 1)
        w = ui->upNext;

    if(w == ui->inProgress)
        t->setEnabled(true);

    QLayout* layout = w->layout();

    connect(t, SIGNAL(toggleCompleted(bool)), this, SLOT(slotToggleCompleted(bool)));

    t->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(t);
}

void MainWindow::moveTask(Task *t, QWidget *d)
{
    if(!t || !d)
        return;

    if(d == ui->inProgress && ui->inProgress->children().count() > 1)
        d = ui->upNext;

    if(d == ui->inProgress)
        t->setEnabled(true);
    else
        t->setEnabled(false);

    t->parentWidget()->layout()->removeWidget(t);
    d->layout()->addWidget(t);

    // update inProgress if necessary
    if(ui->inProgress->children().count() == 1 && ui->upNext->children().count() > 1){
        moveTask(qobject_cast<Task*>(ui->upNext->children().at(1)),ui->inProgress);
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
   if(ui->complete->children().count() <= 1)
       return;

   int reply = QMessageBox::warning(this,tr("Application"),
                                           tr("This will irreversibly delete all completed tasks. Do you want to proceed?"),
                                           QMessageBox::Yes | QMessageBox::No);

   if(reply == QMessageBox::No)
       return;
   if(reply == QMessageBox::Yes){
       while(ui->complete->children().count() > 1){
           Task* t = qobject_cast<Task*>(ui->complete->children().at(1));
           if(t){
               ui->complete->layout()->removeWidget(t);
               delete(t);
           }
       }
   }
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

void MainWindow::slotToggleCompleted(bool completed)
{
    Task* t = qobject_cast<Task*>(sender());
    t->parentWidget()->layout()->removeWidget(t);
    if(completed){
        moveTask(t,ui->complete);
    } else {
        moveTask(t,ui->inProgress);
    }
}
