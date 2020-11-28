#include "paintgrid.h"


PaintGrid::PaintGrid(QQuickItem * parent):
    QQuickPaintedItem(parent)
{

}

PaintGrid::~PaintGrid()
{

}

void PaintGrid::paint(QPainter *painter)
{
    for(int i=0; i<100; i++){
        QPoint p1 = QPoint(0 , i * Constants::tile_width_pixels * sin(1.047));
        QPoint p2 = QPoint(6000 , i * Constants::tile_width_pixels * sin(1.047));
        QPoint p3 = QPoint(i * Constants::tile_width_pixels, 0);
        QPoint p4 = QPoint(i * Constants::tile_width_pixels, 6000);
        painter->drawLine(p1,p2);
        painter->drawLine(p3,p4);

    }

}
