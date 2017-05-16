#ifndef REPL
#define REPL
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QObject>
#include <QString>
#include "mylineitem.hpp"
class QLineEdit;
class REPLWidget: public QWidget
{
    Q_OBJECT
public:
    REPLWidget(QWidget * parent=nullptr);
signals:
    void lineEntered(QString);
private:
    QLabel *label;
    mylineitem * repl_lable;
    QVector<QString> command;
    int command_position = 0;
public slots:
    void up_pressed();
    void down_pressed();
private slots:
    void check_return_pressed();
};
#endif
