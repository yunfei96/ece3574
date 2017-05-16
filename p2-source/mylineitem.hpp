#ifndef MYLINEITEM
#define MYLINEITEM
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QObject>
#include <QString>
class mylineitem:public QLineEdit
{
Q_OBJECT
public:
    void keyPressEvent(QKeyEvent* event);
signals:
    void up_pressed();
    void down_pressed();
};

#endif
