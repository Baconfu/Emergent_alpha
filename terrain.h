#ifndef TERRAIN_H
#define TERRAIN_H


#include <unitspace.h>


class Terrain: public UnitSpace
{
public:
    Terrain(QVector3D position);

    bool collision_player(){return true;}

    QString type(){return QStringLiteral("terrain");}


};

#endif // TERRAIN_H
