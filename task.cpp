#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent, const QString& name) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    m_name = name;
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
    ui->progressBar->setEnabled(enabled);
    ui->checkBox->setEnabled(enabled);
}

void Task::on_lineEdit_textEdited(const QString &arg1)
{
    setName(ui->lineEdit->text());
}
