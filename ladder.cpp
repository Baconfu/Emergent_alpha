#include "ladder.h"
#include "entity.h"
//#include "player.h"
#include "world.h"

Ladder::Ladder(World * worldptr, QVector3D position, int rotation):
    Entity(position,worldptr)
{

}

void Ladder::interact(Entity *)
{

}
