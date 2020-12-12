#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>
#include <QVector3D>


#include <box.h>
#include <unitspace.h>

class World;

class Entity
{
public:
    Entity();
    virtual ~Entity();

    Box * geometry(){return m_geometry;}

    void setRotation(int rotation);
    int getRotation(){return m_rotation;}
    QPoint getCardinalRotation();


    void unregisterFromTiles();

    void setInteractingTiles(QVector<UnitSpace*> tiles);
    void appendInteractingEntity(Entity * e);


    void setVelocity(QVector3D vec){m_velocity = vec;}
    void setVelocityX(float x){m_velocity.setX(x);}
    void setVelocityY(float y){m_velocity.setY(y);}
    void setVelocityZ(float z){m_velocity.setZ(z);}
    QVector3D getVelocity(){return m_velocity;}
    void resetVelocity() {m_velocity = QVector3D (0,0,0);}

    void setAcceleration(QVector3D acc){m_acceleration = acc;}
    void setAccelerationX(float x){m_acceleration.setX(x);}
    void setAccelerationY(float y){m_acceleration.setY(y);}
    void setAccelerationZ(float z){m_acceleration.setZ(z);}
    QVector3D getAcceleration(){return m_acceleration;}

    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj);

    QVector3D previous_position;


    virtual void iterate();
    bool collide(Box box);

    virtual void interact(Entity*) = 0;

    enum state{
        in_air = 0,

        supported = 100,
        climbing = 101,
        detection = 3,
        collision = 4,

    };

    bool getContext(int state) {return m_context_list[state];}
    virtual void setContext(int state, bool desired) {m_context_list.replace(state,desired);}

    void initialiseContextList() {
        for (int i=0; i<contextListLength; i++){
            m_context_list.append(false);
        }
    }


    virtual void updateDisplay();

    void destroy();

protected:



    World * m_worldptr = nullptr;

    QVector<UnitSpace*> interactingTiles;
    QVector<Entity*> interactingEntities;

    Box * m_geometry = nullptr;

    QVector3D m_velocity = QVector3D(0,0,0);

    QVector3D m_acceleration = QVector3D(0,0,-0.1);

    float m_mass = 0;

    QQuickItem * m_obj = nullptr;


private:

    QVector<bool> m_context_list;
    int contextListLength = static_cast<int>(102);

    int m_rotation = 0;




};

#endif // ENTITY_H
