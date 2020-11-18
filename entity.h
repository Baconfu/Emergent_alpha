#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>

class Entity
{
public:
    Entity();

    virtual void setPosition(QPoint pos){m_position = pos;}
    virtual void transform(QPoint vec){m_position+=vec;}

    QPoint getPosition(){return m_position;}
    int getX(){return m_position.x();}
    int getY(){return m_position.y();}

    void setVelocity(QVector2D vec){m_velocity = vec;}
    void setVelocityX(int x){m_velocity.setX(x);}
    void setVelocityY(int y){m_velocity.setY(y);}
    QVector2D getVelocity(){return m_velocity;}

    int getWidth(){return m_width;}
    int getHeight(){return m_height;}

    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj){m_obj = obj;}

protected:
    QPoint m_position;

    QVector2D m_velocity;

    int m_width;
    int m_height;


    QQuickItem * m_obj = nullptr;


};

#endif // ENTITY_H
