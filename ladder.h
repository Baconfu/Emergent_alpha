#ifndef LADDER_H
#define LADDER_H

#include <entity.h>


class Ladder: public Entity
{
public:
    Ladder(QVector3D position, int rotation);
    int span() {return m_span;}


private:
    int m_span;


};


#endif // LADDER_H
