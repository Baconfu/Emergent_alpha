#include "entity.h"

Entity::Entity(QQuickItem * parent):
    QQuickItem(parent)
{

}

void Entity::transform(QPoint vec)
{
    setPosition(position()+vec);

}
