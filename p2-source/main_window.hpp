#ifndef MAIN
#define MAIN
#include <QWidget>
#include "message_widget.hpp"
#include "repl_widget.hpp"
#include "canvas_widget.hpp"
#include "qt_interpreter.hpp"
class msg;
class repl;
class canvas;
class MainWindow: public QWidget
{
Q_OBJECT
public:
    MainWindow(QWidget * parent = nullptr);
    MainWindow(std::string filename, QWidget * parent = nullptr);
private:
    QString text;
    MessageWidget * info;
    REPLWidget * input;
    CanvasWidget * display;
    QtInterpreter * interp;
};
#endif
