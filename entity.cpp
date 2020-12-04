#include "entity.h"
#include <math.h>

#include <constants.h>
#include <ladder.h>
#include <player.h>

Entity::Entity(QVector3D position, World * worldptr)
{
    m_position = position;
    m_worldptr = worldptr;
}

void Entity::setPosition(QVector3D position)
{
    m_position = position;
    m_worldptr->registerEntityToTile(position,this);

}

void Entity::setWidth(float width)
{
    m_dimensions.setX(width);
}

void Entity::setHeight(float height)
{
    m_dimensions.setY(height);
}

void Entity::setDepth(float depth)
{
    m_dimensions.setZ(depth);
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

    m_obj->setZ(currentTilePosition().y());

    updateTilesOccupied();

    updateDisplay();
}

bool Entity::detectionBoxPlayerDetection()
{

}

QVector3D Entity::getGlobalPositionFromLocalPosition(QVector3D box_position, QVector3D local_position)
{
    return box_position + local_position;
}

QVector3D Entity::currentTilePosition()
{
    return QVector3D(m_position.x() / Constants::tile_width_pixels , m_position.y() / Constants::tile_width_pixels , m_position.z() / Constants::tile_width_pixels);
}



void Entity::assignObj(QQuickItem *obj)
{
    m_obj = obj;
}

void Entity::iterate()
{
    if (m_velocity.length() > 0.01) {

        transform(m_velocity);

        /*m_obj->setZ(currentTilePosition().y());

        updateTilesOccupied();

        updateDisplay();*/
    }
}


void Entity::updateDisplay()
{
    QVector3D adjust = QVector3D(m_position.x(),m_position.y(),m_position.z() + m_dimensions.z());
    m_obj->setPosition(World::get2DProjection(adjust));

    m_obj->setWidth(World::get2DProjection(m_dimensions).x());

    QVector3D alt = QVector3D(m_dimensions.x(),m_dimensions.y(),m_dimensions.z()*-1);
    m_obj->setHeight(World::get2DProjection(alt).y());

    m_obj->setZ(float(m_detectionBoxPosition.y()) / Constants::tile_width_pixels + float(m_detectionBoxPosition.z()/100.0/Constants::tile_width_pixels-0.5));
}



