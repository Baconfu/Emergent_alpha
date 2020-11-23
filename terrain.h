#ifndef TERRAIN_H
#define TERRAIN_H

#include <coordinate.h>
#include <unitspace.h>


class Terrain: public UnitSpace
{
public:
    Terrain();

    bool collision_player(){return true;}

    QString type(){return QStringLiteral("terrain");}


};

#endif // TERRAIN_H
