#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <entity.h>
#include <QPolygon>

class Collidable : public Entity
{
public:
    Collidable(QVector3D position);


private:
    QPolygon hitbox;


};

#endif // COLLIDABLE_H
