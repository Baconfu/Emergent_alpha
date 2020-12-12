#ifndef PAINTPLAYERAVATAR_H
#define PAINTPLAYERAVATAR_H

#include <QQuickPaintedItem>

class PaintPlayer: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int m_anim READ anim WRITE setAnim NOTIFY animChanged)
public:
    PaintPlayer(QQuickItem * parent = nullptr);
    ~PaintPlayer();

    void paint(QPainter *painter);

    int anim(){return m_anim;}
    void setAnim(int n){m_anim = n;}
private:
    int m_anim = 0;

signals:
    void animChanged();

};

#endif // PAINTPLAYERAVATAR_H
