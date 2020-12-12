#include "paintuibase.h"

PaintUIBase::PaintUIBase(QQuickItem * parent):
    QQuickPaintedItem(parent)
{

}

PaintUIBase::~PaintUIBase()
{

}

void PaintUIBase::paint(QPainter *painter)
{
    painter->fillRect(0,40,width(),height(),QColor(200,200,200,240));
}



