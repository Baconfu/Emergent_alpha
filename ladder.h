#ifndef LADDER_H
#define LADDER_H

#include <entity.h>


class Ladder: public Entity
{
public:
    Ladder();
    int span() {return m_span;}

private:
    int m_span;
};


#endif // LADDER_H
