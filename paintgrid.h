#ifndef PAINTGRID_H
#define PAINTGRID_H

#include <math.h>
#include <QPainter>
#include <QQuickPaintedItem>

#include <constants.h>


class PaintGrid: public QQuickPaintedItem
{
    Q_OBJECT
public:
    PaintGrid(QQuickItem * parent = nullptr);
    ~PaintGrid();
    void paint(QPainter * painter);
};

#endif // PAINTGRID_H
