#ifndef MYITEM
#define MYITEM
#include <QPainter>
#include <QGraphicsItem>
class QGraphicsArcItem :public QGraphicsEllipseItem
{
public:
    
    QGraphicsArcItem(int x, int y, int z, int k, double angle);
    void paint(QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget *widget);
private:
    double arclength;
    int startangle;
    int endangle;
    double startx;
    double starty;
    double endx;
    double endy;
};
#endif
