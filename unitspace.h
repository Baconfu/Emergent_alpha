#ifndef UNITSPACE_H
#define UNITSPACE_H

#include <QQuickItem>
#include <coordinate.h>

class UnitSpace
{
public:
    UnitSpace(Coordinate c = Coordinate(0,0,0));

    virtual bool collision_player(){return false;}

    int x(){return pos.x();}
    int y(){return pos.y();}
    int z(){return pos.z();}

    void assignObj(QQuickItem * obj);
    QQuickItem * getObj(){return m_obj;}

protected:
    Coordinate pos;

    QQuickItem * m_obj;

};

#endif // UNITSPACE_H
