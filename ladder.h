#ifndef LADDER_H
#define LADDER_H

#include <entity.h>
#include <world.h>

class Ladder: public Entity
{
public:
    Ladder(World * worldptr, QVector3D position, int rotation);
    int getSpan() {return m_span;}

    Entity* getPtr() {return this;}


private:
    int m_span;


};


#endif // LADDER_H
