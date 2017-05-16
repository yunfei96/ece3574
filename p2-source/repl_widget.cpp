#include "repl_widget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QKeyEvent>

REPLWidget::REPLWidget(QWidget * parent)
{
    label = new QLabel(tr("vtscript>"));
    repl_lable = new mylineitem;
    repl_lable->setReadOnly(false);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(repl_lable);
    setLayout(layout);
    QObject::connect(repl_lable, SIGNAL(returnPressed()), this, SLOT(check_return_pressed()));
    QObject::connect(repl_lable, SIGNAL(up_pressed()), this, SLOT(up_pressed()));
    QObject::connect(repl_lable, SIGNAL(down_pressed()), this, SLOT(down_pressed()));
}

void REPLWidget::check_return_pressed()
{
    emit lineEntered(repl_lable->text());
    command.push_back(repl_lable->text());
    command_position = 0;
    repl_lable->clear();
}
void REPLWidget::up_pressed()
{
    if(command_position < command.size())
    {
        repl_lable->setText(command[(command.size()-command_position)-1]);
        command_position++;
    }
}
void REPLWidget::down_pressed()
{
    if(command_position > 0)
    {
        if(command_position == 1)
        {
            repl_lable->clear();
            command_position--;
        }
        else
        {
           repl_lable->setText(command[command.size()-command_position+1]);
            command_position--;
        }
        
    }
}
