#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <entity.h>
#include <QPolygon>

class Collidable : public Entity
{
public:
    Collidable();


private:
    QPolygon hitbox;


};

#endif // COLLIDABLE_H
