#ifndef PAINTTERRAIN_H
#define PAINTTERRAIN_H

#include <QQuickPaintedItem>

#include <constants.h>

class PaintTerrain: public QQuickPaintedItem
{
public:
    PaintTerrain(QQuickItem * parent = nullptr);
    ~PaintTerrain();

    void paint(QPainter *painter);
};

#endif // PAINTTERRAIN_H
