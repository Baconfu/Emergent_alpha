#include "paintplayeravatar.h"
#include <math.h>
#include <QPainter>
#include <QImage>

#include <constants.h>


PaintPlayerAvatar::PaintPlayerAvatar(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

PaintPlayerAvatar::~PaintPlayerAvatar()
{

}

void PaintPlayerAvatar::paint(QPainter *painter)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);



    painter->setPen(pen);
    float diff = abs(10*sin(0.1*anim()));
    float h = Constants::player_height_pixels - 10 +diff;
    QRect top = QRect(0,10-diff,width(), Constants::player_width_pixels * sin(1.047));
    QRect side = QRect(0,10-diff + Constants::player_width_pixels * sin(1.047),width(),h);
    painter->fillRect(top,QColor::fromRgb(200,200,200));
    painter->fillRect(side,QColor::fromRgb(70,70,70));

}
