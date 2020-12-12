#include "ladder.h"
#include "entity.h"
//#include "player.h"
#include "world.h"

Ladder::Ladder():
    Entity()
{
    setContext(detection,true);
}
