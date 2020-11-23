#ifndef UNITSPACE_H
#define UNITSPACE_H

#include <QString>
#include <QStringLiteral>
#include <QQuickItem>


#include <coordinate.h>


class UnitSpace
{
public:
    UnitSpace(Coordinate c = Coordinate(0,0,0));

    virtual bool collision_player(){return false;}

    virtual QString type(){return QString();}

    int x(){return pos.x();}
    int y(){return pos.y();}
    int z(){return pos.z();}

    virtual void setPosition(Coordinate c);

    void assignObj(QQuickItem * obj);
    QQuickItem * getObj(){return m_obj;}

protected:
    Coordinate pos;

    QQuickItem * m_obj;

};

#endif // UNITSPACE_H
