#include "qgraphics_arc_item.hpp"
#include  <cmath>
#define PI 3.14159265

QGraphicsArcItem::QGraphicsArcItem(int x, int y, int z, int k, double angle)
{
    double r = sqrt(pow((k-y),2)+pow((z-x),2));
    startx = x-r;
    starty = y-r;
    endx = 2*r;
    endy = 2*r;
    arclength = sqrt(pow((z-(x+r)),2)+pow((k-y),2));
    startangle = 2* asin (arclength/(2*r)) * 180.0 / PI;
    if(y>k)
    {
        startangle = 360-startangle;
        endangle = -angle*180/PI;
    }
    else
    {
        endangle = angle*180/PI;
    }
    setRect(QRectF(startx, starty, endx, endy));
    setStartAngle(startangle*16);
    setSpanAngle(endangle*16);
}


void QGraphicsArcItem:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawArc(startx, starty, endx, endy, startangle*16,endangle*16);
}

