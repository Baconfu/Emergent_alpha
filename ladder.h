#ifndef LADDER_H
#define LADDER_H

#include <entity.h>
#include <world.h>

class Ladder: public Entity
{
public:
    Ladder();

    int getSpan() {return m_span;}

    void interact(Entity *){}


private:
    int m_span;


};


#endif // LADDER_H
