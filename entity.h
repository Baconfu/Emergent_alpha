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

    Box * geometry(){return m_geometry;}

    QVector3D getCenter(){return m_geometry->position() + m_geometry->dimensions()/2;}

    void setRotation(int rotation);
    int getRotation(){return m_rotation;}
    QPoint getCardinalRotation() {
        if (m_rotation == 0) {return QPoint(0,-1);}
        if (m_rotation == 1) {return QPoint(1,0);}
        if (m_rotation == 2) {return QPoint(0,1);}
        if (m_rotation == 3) {return QPoint(-1,0);}
        return QPoint(0,0);
    }

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
    virtual void onDetectingEntity(Entity*) = 0;
    virtual void onDepartingEntity(Entity*) = 0;

    enum state{
        in_air = 0,

        supported = 2,
        detection = 3,
        collision = 4,
        climbing = 20,
    };

    bool getContext(int state) {return m_context_list[state];}
    virtual void setContext(int state, bool desired) {m_context_list.replace(state,desired);}
    virtual void updateContext(){
        if (int(m_position.z()) % Constants::tile_width_pixels > Constants::tile_width_pixels - 5 ||
                getSpacesSupporting().length() == 0){
            setContext(in_air,true);
        }
        if (getSpacesSupporting().length() != 0){
            setContext(in_air,false);
            setContext(supported,true);
        }
    }
    virtual void resolveContext(){
        if (getContext(in_air) == true || getContext(supported) == false){
            setAccelerationZ(- float(Constants::gravity_per_second) / (1000/float(Constants::tick_duration)));
            qDebug()<<"acceleration setted"<<float(Constants::gravity_per_second) / (1000/float(Constants::tick_duration));
        }
        if (getContext(supported) == true) {setAcceleration(QVector3D(0,0,0));}
    }

    void iterateTransformation();

    void initialiseContextList() {
        for (int i=0; i<contextListLength; i++){
            m_context_list.append(false);
        }
    }

    QVector<Entity*> getProximalEntities() {return m_proximal_entities;}
    void addProximalEntities(Entity* e) {m_proximal_entities.append(e);}
    void clearProximalEntities() {m_proximal_entities.clear();}
    void removeAllFromProximalEntities(Entity* e) {m_proximal_entities.removeAll(e);}
    //virtual void updateProximalEntities();

    virtual void updateDisplay();

protected:
    World * m_worldptr = nullptr;

    UnitSpace * current_space = nullptr;

    Box * m_geometry;

    QVector3D m_velocity;

    QVector3D m_acceleration;

    float m_mass;

    QQuickItem * m_obj = nullptr;


private:

    QVector<bool> m_context_list;
    int contextListLength = static_cast<int>(Entity::count);

    int m_rotation = 0;




};

#endif // ENTITY_H
