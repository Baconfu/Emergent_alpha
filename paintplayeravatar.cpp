#include "paintplayeravatar.h"
#include <QPainter>
#include <QImage>


PaintPlayerAvatar::PaintPlayerAvatar(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

PaintPlayerAvatar::~PaintPlayerAvatar()
{

}

void PaintPlayerAvatar::paint(QPainter *painter)
{
    painter->drawRect(QRect(0,0,width(),height()-anim_cycle()));

}
