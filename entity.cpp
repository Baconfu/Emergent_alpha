#include "entity.h"
#include <math.h>

#include <constants.h>
#include <ladder.h>
#include <player.h>
#include <chunk.h>

Entity::Entity()
{
    m_geometry = new Box();
    initialiseContextList();
}

Entity::~Entity()
{
    m_obj->deleteLater();
    delete(m_geometry);
}

void Entity::setRotation(int rotation)
{
    m_rotation = rotation;
}

QPoint Entity::getCardinalRotation() {
    if (m_rotation == 0) {return QPoint(0,-1);}
    if (m_rotation == 1) {return QPoint(1,0);}
    if (m_rotation == 2) {return QPoint(0,1);}
    if (m_rotation == 3) {return QPoint(-1,0);}
    return QPoint(0,0);
}

void Entity::unregisterFromTiles()
{
    for(int i=0; i<interactingTiles.length(); i++){
        interactingTiles[i]->removeEntity(this);
    }
    interactingTiles.clear();
}


void Entity::setInteractingTiles(QVector<UnitSpace *> tiles)
{
    interactingTiles = tiles;
    for(int i=0; i<interactingTiles.length(); i++){
        interactingTiles[i]->assignEntity(this);
        QVector<Entity*> entities = interactingTiles[i]->getEntitiesOnTile();
        for(int j=0; j<entities.length(); j++){
            if(!interactingEntities.contains(entities[j])){
                appendInteractingEntity(entities[j]);
                entities[j]->appendInteractingEntity(this);
            }
        }
    }
}

void Entity::appendInteractingEntity(Entity *e)
{
    interactingEntities.append(e);
}

void Entity::assignObj(QQuickItem *obj)
{
    m_obj = obj;
}

void Entity::iterate()
{


    if (m_acceleration.length() > 0.01){
        //setVelocity(getVelocity()+getAcceleration());
    }

    if (m_velocity.length() > 0.01) {
        m_geometry->transform(m_velocity);
    }

    for(int i=0; i<interactingEntities.length(); i++){
        interact(interactingEntities[i]);
    }
    for(int i=0; i<interactingTiles.length(); i++){
        if(interactingTiles[i]->collision_player()){
            collide(interactingTiles[i]->getBox());
        }

    }

    updateDisplay();

}

bool Entity::collide(Box box)
{
    QVector3D v1 = m_geometry->get111() - box.get000();
    QVector3D v2 = m_geometry->get000() - box.get111();

    if(v2.x() < 0 && v2.y() < 0 && v2.z() < 0 && v1.x() > 0 && v1.y() > 0 && v1.z() > 0){
        //entity box overlaps with space


        //transform vector: shortest distance to get the entity outside of the space.
        QVector3D transform = QVector3D(100,100,100);

        if(v2.x() * -1 < transform.length()){
            transform = QVector3D(v2.x(), 0, 0);
        }
        if(v2.y() * -1 < transform.length()){
            transform = QVector3D(0, v2.y(), 0);
        }
        if(v2.z() * -1 < transform.length()){
            transform = QVector3D(0, 0, v2.z());
        }
        if(v1.x() < transform.length()){
            transform = QVector3D(v1.x(), 0, 0);
        }
        if(v1.y() < transform.length()){
            transform = QVector3D(0, v1.y(), 0);
        }
        if(v1.z() < transform.length()){
            transform = QVector3D(0, 0, v1.z());
        }
        transform *= -1;

        m_geometry->transform(transform*0.99);

        //the velocity of the entity on the axis of collision should be set to 0.
        //the axis of collision corresponds to the non-zero part of QVector3D transform.


        return true;

    }

    return false;

}



/*void Entity::updateProximalEntities()
{
    for (int i = 0; i<m_tiles_occupied.length(); i++){
        for (int j = 0; j<Chunk::getSpacePtrFromLocalTilePosition(m_tiles_occupied[i])->getEntitiesOnTile().length(); j++){
            m_proximal_entities.append(Chunk::getSpacePtrFromLocalTilePosition(World::getLocalTilePositionFromGlobalPosition(m_tiles_occupied[i]))->getEntitiesOnTile()[j]);

        }
    }
}*/


void Entity::updateDisplay()
{
    m_obj->setPosition(World::get2DProjection(m_geometry->get001()));

    m_obj->setWidth(m_geometry->width());
    m_obj->setHeight(World::get2DProjection(m_geometry->get110()).y() - World::get2DProjection(m_geometry->get001()).y());

    m_obj->setZ(float(m_geometry->get110().y()-0.1) / Constants::tile_width_pixels + float(m_geometry->get110().z()/100.0/Constants::tile_width_pixels));
}

void Entity::destroy()
{
    m_obj->deleteLater();
    delete(m_geometry);
}



