#ifndef AIR_H
#define AIR_H



#include <unitspace.h>

class Air: public UnitSpace
{
public:
    Air(QVector3D position);

    QString type(){return QStringLiteral("air");}

    bool collision_player(){return false;}
};

#endif // AIR_H
