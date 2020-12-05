#include "ladder.h"
#include "entity.h"
//#include "player.h"
#include "world.h"

Ladder::Ladder(World * worldptr, QVector3D position, int rotation):
    Entity(position,worldptr)
{
    enableDetection();
}

void Ladder::onDetectingEntity(Entity *)
{

}

void Ladder::onDepartingEntity(Entity *)
{

}
