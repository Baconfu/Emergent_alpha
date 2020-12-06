#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>
#include <QVector3D>


#include <unitspace.h>

class World;

class Entity
{
public:
    Entity(QVector3D getPosition,World * worldPtr);

    QVector3D getPosition(){return m_position;}

    QVector3D getCenter(){return m_position + m_dimension/2;}

    void setPosition(QVector3D getPosition);
    void setPositionX(float x){m_position.setX(x);}
    void setPositionY(float y){m_position.setY(y);}
    void setPositionZ(float z){m_position.setZ(z);}
    float x(){return m_position.x();}
    float y(){return m_position.y();}
    float z(){return m_position.z();}

    QVector3D getDimension(){return m_dimension;}
    void setDimension(QVector3D dimensions){m_dimension = dimensions;}
    void setDimensionX(float getDimensionX);
    void setDimensionY(float getDimensionY);
    void setDimensionZ(float getDimensionZ);
    float getDimensionX(){return m_dimension.x();}
    float getDimensionY(){return m_dimension.y();}
    float getDimensionZ(){return m_dimension.z();}

    void setRotation(int getRotation);
    int getRotation(){return m_rotation;}
    QPoint getCardinalRotation() {
        if (m_rotation == 0) {return QPoint(0,-1);}
        if (m_rotation == 1) {return QPoint(1,0);}
        if (m_rotation == 2) {return QPoint(0,1);}
        if (m_rotation == 3) {return QPoint(-1,0);}
    }

    void transform(QVector3D vector);

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

    void setDetectionBoxPosition(QVector3D newPosition) {m_detectionBoxPosition = newPosition;}
    void setDetectionBoxDimension(QVector3D newDimension) {m_detectionBoxDimension = newDimension;}
    QVector3D getDetectionBoxPosition(){return m_detectionBoxPosition;}
    QVector3D getDetectionBoxDimension(){return m_detectionBoxDimension;}
    QVector3D getDetectionBoxDimensionGlobalPosition() {return m_detectionBoxPosition + m_detectionBoxDimension;}

    void setCollisionBoxPosition(QVector3D newPosition) {m_collisionBoxPosition = newPosition;}
    void setCollisionBoxDimension(QVector3D newDimension) {m_collisionBoxDimension = newDimension;}
    QVector3D getCollisionBoxPosition(){return m_collisionBoxPosition;}
    QVector3D getCollisionBoxDimension(){return m_collisionBoxDimension;}
    QVector3D getCollisionBoxDimensionGlobalPosition() {return m_collisionBoxPosition + m_collisionBoxDimension;}

    static QVector3D getGlobalPositionFromLocalPosition(QVector3D box_position, QVector3D local_position);

    virtual QVector3D getCurrentTilePosition();
    UnitSpace * getCurrentTile(){return current_space;}
    void setCurrentTile(UnitSpace * space){current_space = space;}

    virtual Entity* getSpecificPtr() {return nullptr;}
    Entity * getEntityPtr(){return this;}


    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj);

    void updateTilesOccupied() {m_tiles_occupied = World::getTilesOccupiedPosition(this);}
    QVector<QVector3D> getTilesOccupied() {return m_tiles_occupied;}

    QVector3D m_previous_position;


    virtual void iterate();
    virtual void onDetectingEntity(Entity*) = 0;
    virtual void onDepartingEntity(Entity*) = 0;

    enum state{
        in_air = 0,
        below_zero = 1,
        detection = 2,
        collision = 3,
        climbing = 20,

        count
    };

    bool getContext(int state) {return m_context_list[state];}
    virtual void setContext(int state, bool desired) {m_context_list.replace(state,desired);}
    virtual void updateContext();
    virtual void resolveContext();

    bool getDetectionState() {return getContext(detection);}
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

    QVector3D m_position;

    QVector3D m_dimension;

    QVector3D m_velocity;

    QVector3D m_acceleration;

    float m_mass;

    QQuickItem * m_obj = nullptr;


private:
    float m_depth = 0;

    QVector<QVector3D> m_tiles_occupied = QVector<QVector3D>();

    QVector<Entity*> m_proximal_entities = QVector<Entity*>();



    QVector<bool> m_context_list;
    int contextListLength = static_cast<int>(Entity::count);

    int m_rotation = 0;

    QVector3D m_detectionBoxPosition = QVector3D (0,0,0);
    QVector3D m_detectionBoxDimension = QVector3D (0,0,0);

    QVector3D m_collisionBoxPosition = QVector3D (0,0,0);
    QVector3D m_collisionBoxDimension = QVector3D (0,0,0);

};

#endif // ENTITY_H
