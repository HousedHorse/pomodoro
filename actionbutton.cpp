#include "actionbutton.h"

ActionButton::ActionButton(QWidget *parent) : QPushButton (parent)
{

}

ActionButton::~ActionButton()
{

}

void ActionButton::updateButtonStatusFromAction()
{
    if(!m_action)
        return;

    //setText(m_action->text());
    setStatusTip(m_action->statusTip());
    setToolTip(m_action->toolTip());
    setIcon(m_action->icon());
    setEnabled(m_action->isEnabled());
    setCheckable(m_action->isCheckable());
    setChecked(m_action->isChecked());
}

void ActionButton::setAction(QAction *action)
{
    // disconnect previous action if necessary
    if(m_action && m_action != action){
        disconnect(m_action, &QAction::changed,
                   this, &ActionButton::updateButtonStatusFromAction);
        disconnect(this, &ActionButton::clicked,
                   m_action, &QAction::trigger);
    }

    m_action = action;

    updateButtonStatusFromAction();

    connect(m_action, &QAction::changed,
            this, &ActionButton::updateButtonStatusFromAction);

    connect(this, &ActionButton::clicked,
            m_action, &QAction::trigger);
}
