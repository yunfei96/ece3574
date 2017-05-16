#ifndef CANVAS
#define CANVAS
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
class QLabel;
class CanvasWidget: public QWidget
{
    Q_OBJECT
public:
    CanvasWidget(QWidget * parent = nullptr);
public slots:
    void addGraphic(QGraphicsItem * item);
private:
    QGraphicsView * canvas_view;
    QGraphicsScene * scene;
    
};
#endif
