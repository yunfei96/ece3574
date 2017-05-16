#ifndef QTINTER
#define QTINTER
#include <QWidget>
#include "interpreter.hpp"
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "qgraphics_arc_item.hpp"
#include <string>
class QtInterpreter:public QWidget
{
Q_OBJECT
public:
    QtInterpreter(QObject * parent = nullptr);
    void readfile(std::istream & expression);
signals:
    void drawGraphic(QGraphicsItem * item);
    void info(QString message);
    void error(QString message);
public slots:
    void parseAndEvaluate(QString entry);
    
private:
    void draw();
    Interpreter interp;
    bool calndis(bool ok);
    QString result;
};
#endif

