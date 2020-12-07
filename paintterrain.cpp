#include "paintterrain.h"

#include <math.h>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QString>


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

    QStringList s = QString::number(z()).split(".");

    int level = 0;
    if(s.length() > 1){
        level = s[1].toInt();
    }

    //painter->drawRect(QRect(0,30*sin(1.047),30,height()-30*sin(1.047)));

    painter->fillRect(QRect(0,Constants::tile_width_pixels*sin(1.047),Constants::tile_width_pixels,height()-Constants::tile_width_pixels*sin(1.047)),QColor::fromRgb(70 + level*40, 70 + level*40 , 70 + level*40));

    painter->fillRect(QRect(0,0,width(),Constants::tile_width_pixels*sin(1.047)),QColor::fromRgb(160 + level*30 , 160 + level*30 , 160 + level*30));

}
