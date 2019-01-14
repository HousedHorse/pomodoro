#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QPushButton>
#include <QAction>

class ActionButton : public QPushButton
{
public:
    explicit ActionButton(QWidget* parent = nullptr);
    ~ActionButton();

    void setAction(QAction *action);

public slots:
    void updateButtonStatusFromAction();

private:
    QAction* m_action = nullptr;
};

#endif // ACTIONBUTTON_H
