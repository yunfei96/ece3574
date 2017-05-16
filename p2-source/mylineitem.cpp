#include "mylineitem.hpp"
#include <QDebug>
#include <QKeyEvent>
void mylineitem::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Down)
    {
        emit down_pressed();
    }
    if(event->key() == Qt::Key_Up)
    {
        emit up_pressed();
    }
    QLineEdit::keyPressEvent(event);
    
    
}
