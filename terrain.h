#ifndef TERRAIN_H
#define TERRAIN_H

#include <coordinate.h>
#include <unitspace.h>


class Terrain: public UnitSpace
{
public:
    Terrain(Coordinate pos);

    bool collision_player(){return true;}


};

#endif // TERRAIN_H
