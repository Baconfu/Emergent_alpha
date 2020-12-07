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



    QVector3D getCenter(){return m_position + m_dimension/2;}

    void setPosition(QVector3D getPosition);
    void setPositionX(float x){m_position.setX(x);}
    void setPositionY(float y){m_position.setY(y);}
    void setPositionZ(float z){m_position.setZ(z);}
    QVector3D getPosition(){return m_position;}
    float getPositionX() {return m_position.x();}
    float getPositionY() {return m_position.y();}
    float getPositionZ() {return m_position.z();}
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
    virtual Entity * getEntityPtr(){return this;}


    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj);

    void updateSpacesOccupied() {m_spaces_occupied.clear(); m_spaces_occupied = World::getTilesOccupiedTilePosition(this);}
    QVector<QVector3D> getSpacesOccupied() {return m_spaces_occupied;}
    void updateSpacesSupporting() {m_spaces_supporting.clear(); m_spaces_supporting = getSpacesSupporting();}
    QVector<UnitSpace*> getSpacesSupporting();

    QVector3D m_previous_position;


    virtual void iterate();
    virtual void onDetectingEntity(Entity*) = 0;
    virtual void onDepartingEntity(Entity*) = 0;

    enum state{
        in_air = 0,

        supported = 2,
        detection = 3,
        collision = 4,
        climbing = 20,

        count
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

    QVector<QVector3D> m_spaces_occupied = QVector<QVector3D>();
    QVector<UnitSpace*> m_spaces_supporting = QVector<UnitSpace*>();

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
