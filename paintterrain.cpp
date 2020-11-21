#include "paintterrain.h"

#include <math.h>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>


PaintTerrain::PaintTerrain(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

PaintTerrain::~PaintTerrain()
{

}

void PaintTerrain::paint(QPainter *painter)
{
    QPen pen;
    pen.setWidth(2);
    QBrush brush;
    brush.setColor("grey");


    painter->setPen(pen);
    painter->setBrush(brush);

    //painter->drawRect(QRect(0,30*sin(1.047),30,height()-30*sin(1.047)));
    painter->fillRect(QRect(0,30*sin(1.047),30,height()-30*sin(1.047)),QColor::fromRgb(70,70,70));

    painter->fillRect(QRect(0,0,width(),30*sin(1.047)),QColor::fromRgb(200,200,200));

}
