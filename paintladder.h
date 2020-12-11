#ifndef PAINTLADDER_H
#define PAINTLADDER_H

#include <QDir>
#include <QImage>
#include <QQuickPaintedItem>
#include <ladder.h>

class PaintLadder: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int m_painted_rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    PaintLadder(QQuickItem* parent = nullptr);
    ~PaintLadder();

    void paint(QPainter *painter);

    void setRotation(int r){m_painted_rotation = r; emit rotationChanged();}

    int rotation(){return m_painted_rotation;}

private:
    QImage src;
    int m_painted_rotation;

signals:
    void rotationChanged();

};

#endif // PAINTLADDER_H
