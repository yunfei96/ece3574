#include "message_widget.hpp"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

MessageWidget::MessageWidget(QWidget * parent)
{
    label = new QLabel(tr("Message:"));
    msg_lable = new QLineEdit;
    msg_lable->setReadOnly(true);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(msg_lable);
    setLayout(layout);
}

void MessageWidget::info(QString message)
{
    msg_lable->clear();
    msg_lable->setText(message);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Highlight,Qt::white);
    msg_lable->setPalette(*palette);
}

void MessageWidget::error(QString message)
{
    
    msg_lable->clear();
    msg_lable->setText(message);
    QPalette *palette = new QPalette();
    msg_lable->selectAll();
    palette->setColor(QPalette::Highlight,Qt::red);
    msg_lable->setPalette(*palette);

}
