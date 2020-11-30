#include "ladder.h"
#include "entity.h"

Ladder::Ladder(QVector3D position, int rotation):
    Entity(position)
{
    setRotation(rotation);
    setPosition(position);
}

