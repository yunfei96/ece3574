#include "canvas_widget.hpp"
#include <QGraphicsView>
#include <QHBoxLayout>
#include "qgraphics_arc_item.hpp"
#include <QDebug>
CanvasWidget::CanvasWidget(sc)
{
    //set canvas
    canvas_view = new QGraphicsView();
    //set scene
    
    scene = new QGraphicsScene(canvas_view);
    canvas_view->setScene(scene);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(canvas_view);
    setLayout(layout);
}

void CanvasWidget::addGraphic(QGraphicsItem * item)
{
    scene->addItem(item);
    scene->update();

}

