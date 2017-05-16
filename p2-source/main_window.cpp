#include "main_window.hpp"
#include <QLayout>
#include <fstream>
#include <QDebug>
MainWindow::MainWindow(QWidget * parent)
{
    this->setMinimumSize(800, 600);
    info = new MessageWidget(nullptr);
    input = new REPLWidget(nullptr);
    display = new CanvasWidget(nullptr);
    interp = new QtInterpreter();
    auto layout = new QGridLayout;
    layout -> addWidget(info, 1, 0);
    layout -> addWidget(input, 3,0);
    layout -> addWidget(display, 2,0);
    setLayout(layout);
    //-----connect with self
    QObject::connect(input, SIGNAL(lineEntered(QString)), interp, SLOT(parseAndEvaluate(QString)));
    QObject::connect(interp, SIGNAL(info(QString)), info, SLOT(info(QString)));
    QObject::connect(interp, SIGNAL(error(QString)), info, SLOT(error(QString)));
    QObject::connect(interp, SIGNAL(drawGraphic(QGraphicsItem *)), display, SLOT(addGraphic(QGraphicsItem * )));
}

MainWindow::MainWindow(std::string filename, QWidget * parent)
{
    this->setMinimumSize(800, 600);
    info = new MessageWidget(nullptr);
    input = new REPLWidget(nullptr);
    display = new CanvasWidget(nullptr);
    interp = new QtInterpreter();
    auto layout = new QGridLayout;
    layout -> addWidget(info, 1, 0);
    layout -> addWidget(input, 3,0);
    layout -> addWidget(display, 2,0);
    setLayout(layout);
    //-----connect with self
    QObject::connect(input, SIGNAL(lineEntered(QString)), interp, SLOT(parseAndEvaluate(QString)));
    QObject::connect(interp, SIGNAL(info(QString)), info, SLOT(info(QString)));
    QObject::connect(interp, SIGNAL(error(QString)), info, SLOT(error(QString)));
    QObject::connect(interp, SIGNAL(drawGraphic(QGraphicsItem *)), display, SLOT(addGraphic(QGraphicsItem * )));
    ifstream in(filename);
    if(!in.is_open())
    {
        info->error("Error: cannot open file");
    }
    else
    {
       interp->readfile(in);
    }
    
}
