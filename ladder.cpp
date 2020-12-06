#include "ladder.h"
#include "entity.h"
//#include "player.h"
#include "world.h"

Ladder::Ladder(World * worldptr, QVector3D position, int rotation):
    Entity(position,worldptr)
{
    setContext(detection,true);
}

void Ladder::onDetectingEntity(Entity *)
{

}

void Ladder::onDepartingEntity(Entity *)
{

}

void Ladder::updateContext()
{

}

void Ladder::resolveContext()
{

}
