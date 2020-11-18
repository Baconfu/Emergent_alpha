#include "world.h"

World::World(QPoint coordinates)
{
    //load world from coordinates
    //coordinates should refer to player position upon spawn



}

void World::iterate()
{

}

void World::keyInputs(int event_key)
{
    switch(event_key){
    case 65:
        player->setVelocityX(-1);
        break;
    case 83:
        player->setVelocityY(1);
        break;
    case 68:
        player->setVelocityX(1);
        break;
    case 87:
        player->setVelocityY(-1);
    }
}

void World::keyRelease(int event_key)
{
    switch(event_key){
    case 65:
        if(player->getVelocity().x()==-1){
            player->setVelocityX(0);
        }
        break;
    case 83:
        player->setVelocityY(1);
        break;
    case 68:
        player->setVelocityX(1);
        break;
    case 87:
        player->setVelocityY(-1);
}

