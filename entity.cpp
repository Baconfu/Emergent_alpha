#include "entity.h"

#include <constants.h>

Entity::Entity(QQuickItem * parent):
    QQuickItem(parent)
{

}

void Entity::transform(QPoint vec)
{
    setPosition(position()+vec);

}

QPoint Entity::currentTile()
{
    return QPoint(position().x() / Constants::tile_width_pixels,position().y() / Constants::tile_width_pixels);
}
