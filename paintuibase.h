#ifndef PAINTUIBASE_H
#define PAINTUIBASE_H

#include <QPainter>
#include <QQuickPaintedItem>
#include <QRgba64>


class PaintUIBase: public QQuickPaintedItem
{
    Q_OBJECT
public:
    PaintUIBase(QQuickItem * parent = nullptr);
    ~PaintUIBase();

    void paint(QPainter *painter);


};

#endif // PAINTUIBASE_H
