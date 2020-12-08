#include "unitspace.h"
#include <math.h>

UnitSpace::UnitSpace(QVector3D position)
{

    m_position = position;

}

Box UnitSpace::getBox()
{
    Box b;
    b.setPosition(m_position * Constants::tile_width_pixels);
    b.setDimensions(m_dimensions * Constants::tile_width_pixels);
    return b;
}

void UnitSpace::setPosition(QVector3D position)
{
    m_position = position;
}

void UnitSpace::assignObj(QQuickItem *obj)
{
    m_obj = obj;
}

void UnitSpace::updateDisplay()
{
    QVector3D adjust = QVector3D(m_position.x(),m_position.y(),m_position.z() + 1);
    m_obj->setPosition(World::get2DProjection(adjust * Constants::tile_width_pixels));
    m_obj->setWidth(World::get2DProjection(m_dimensions * Constants::tile_width_pixels).x());
    QVector3D alt = QVector3D(m_dimensions.x(),m_dimensions.y(),m_dimensions.z() * -1.0);
    m_obj->setHeight(World::get2DProjection(alt * Constants::tile_width_pixels).ry());
    m_obj->setZ(float(m_position.y()) + float(m_position.z())/100.0);
}

