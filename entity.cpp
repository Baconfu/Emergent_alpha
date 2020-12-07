#include "entity.h"
#include <math.h>

#include <constants.h>
#include <ladder.h>
#include <player.h>
#include <chunk.h>

Entity::Entity()
{
    m_geometry = new Box;
    initialiseContextList();
}

void Entity::setPosition(QVector3D position)
{
    m_previous_position = m_position;
    m_position = position;

    //register entity to tile is driven by the entity itself, so it is only run when necessary
    //(when the entity has moved)
    m_worldptr->registerEntityToTile(position,this);
}

void Entity::setDimensionX(float width)
{
    m_dimension.setX(width);
}

void Entity::setDimensionY(float height)
{
    m_dimension.setY(height);
}

void Entity::setDimensionZ(float depth)
{
    m_dimension.setZ(depth);
}

void Entity::setRotation(int rotation)
{
    m_rotation = rotation;
}

void Entity::transform(QVector3D vector)
{
    setPosition(m_position + vector);
    setDetectionBoxPosition(m_detectionBoxPosition + vector);
    //___________________________________________

    m_obj->setZ(getTilePosition().y());

    updateSpacesOccupied();

    updateDisplay();
}





QVector3D Entity::getGlobalPositionFromLocalPosition(QVector3D box_position, QVector3D local_position)
{
    return box_position + local_position;
}

QVector3D Entity::getTilePosition()
{
    return QVector3D(m_position.x() / Constants::tile_width_pixels , m_position.y() / Constants::tile_width_pixels , m_position.z() / Constants::tile_width_pixels);
}

QVector<QVector3D> Entity::getOccupiedTilePositions()
{
    QVector<QVector3D> out;

    QVector3D up_left_bottom_tile = m_position/Constants::tile_width_pixels;
    QVector3D down_right_top_tile = (m_position + m_dimension)/Constants::tile_width_pixels;

    for (int i = up_left_bottom_tile[0] ; i<(down_right_top_tile[0]+1) ; i++){
        for (int j = up_left_bottom_tile[1] ; j<(down_right_top_tile[1]+1) ; j++){
            for (int k = up_left_bottom_tile[2] ; k<(down_right_top_tile[2]+1) ; k++){
                    out.append(QVector3D(i,j,k));
            }
        }
    }

    return out;
}



void Entity::assignObj(QQuickItem *obj)
{
    m_obj = obj;
}

QVector<UnitSpace*> Entity::getSpacesSupporting()
{
    QVector<UnitSpace*> out = QVector<UnitSpace*>();
    if (int(getPositionZ()) % 30 >= 1) {return out;}

    QVector3D bottom_up_left_corner = m_position + QVector3D(0,0,-1);
    QVector3D bottom_down_right_corner = m_position + QVector3D(m_dimension.x(),m_dimension.y(),-1);

    QVector<UnitSpace*> spaces_below = m_worldptr->getTilePtrListFromPixel(bottom_up_left_corner,bottom_down_right_corner);
    for (int i=0; i<spaces_below.length(); i++){
        if (typeid(*spaces_below[i]) == typeid(Terrain)){
            out.append(spaces_below[i]);
        }
    }
    return out;
}

void Entity::iterate()
{
    updateContext();
    resolveContext();

    iterateTransformation();




}

void Entity::iterateTransformation()
{

    if (m_acceleration.length() > 0.01){
        setVelocity(getVelocity()+getAcceleration());
    }
    if (m_velocity.length() > 0.01) {
        transform(m_velocity);
    }

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

    QVector3D adjust = QVector3D(m_position.x(),m_position.y(),m_position.z() + m_dimension.z());
    //qDebug()<<"checkpoint1";
    m_obj->setPosition(World::get2DProjection(adjust));

    m_obj->setWidth(World::get2DProjection(m_dimension).x());

    QVector3D alt = QVector3D(m_dimension.x(),m_dimension.y(),m_dimension.z()*-1);
    m_obj->setHeight(World::get2DProjection(alt).y());

    m_obj->setZ(float(m_detectionBoxPosition.y()) / Constants::tile_width_pixels + float(m_detectionBoxPosition.z()/100.0/Constants::tile_width_pixels-0.5));
}



