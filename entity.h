#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>

class Entity: public QQuickItem
{
    Q_OBJECT
public:
    Entity(QQuickItem * parent = nullptr);


    virtual void transform(QPoint vec);

    void setVelocity(QVector2D vec){m_velocity = vec;}
    void setVelocityX(int x){m_velocity.setX(x);}
    void setVelocityY(int y){m_velocity.setY(y);}
    QVector2D getVelocity(){return m_velocity;}

    virtual QPoint currentTile();


    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj){m_obj = obj;}

protected:

    QVector2D m_velocity;



    QQuickItem * m_obj = nullptr;


};

#endif // ENTITY_H
