#ifndef PAINTPLAYERAVATAR_H
#define PAINTPLAYERAVATAR_H

#include <QQuickPaintedItem>

class PaintPlayerAvatar: public QQuickPaintedItem
{
    Q_PROPERTY(int m_anim_cycle READ anim_cycle WRITE setAnim_cycle NOTIFY anim_cycleChanged)
public:
    PaintPlayerAvatar(QQuickItem * parent = nullptr);
    ~PaintPlayerAvatar();

    void paint(QPainter *painter);

    int anim_cycle(){return m_anim_cycle;}
    void setAnim_cycle(int n){m_anim_cycle = n;}
private:
    int m_anim_cycle;

signals:
    void anim_cycleChanged();

};

#endif // PAINTPLAYERAVATAR_H
