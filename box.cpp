#include "box.h"

#include <constants.h>
#include <QDebug>

Box::Box()
{

}

QVector3D Box::get000()
{
    return m_position;
}

QVector3D Box::get001()
{
    return QVector3D(m_position.x(),m_position.y(),m_position.z() + m_dimensions.z());
}
QVector3D Box::get010()
{
    return QVector3D(m_position.x(),m_position.y()+m_dimensions.y(),m_position.z());
}

QVector3D Box::get011()
{
    return QVector3D(m_position.x(),m_position.y()+m_dimensions.y(),m_position.z()+m_dimensions.z());
}

QVector3D Box::get100()
{
    return QVector3D(m_position.x()+m_dimensions.x(),m_position.y(),m_position.z());
}

QVector3D Box::get101()
{
    return QVector3D(m_position.x()+m_dimensions.x(),m_position.y(),m_position.z()+m_dimensions.z());
}

QVector3D Box::get110()
{
    return QVector3D(m_position.x()+m_dimensions.x(),m_position.y()+m_dimensions.y(),m_position.z());
}

QVector3D Box::get111()
{
    return QVector3D(m_position.x()+m_dimensions.x(),m_position.y()+m_dimensions.y(),m_position.z()+m_dimensions.z());
}

void Box::rotate(int direction)
{

    /* WORK IN PROGRESS
    int delta = direction - rotation;
    if(delta<0){
        delta +=4;
    }
    delta*/

}

QVector<QVector3D> Box::getOccupiedTiles()
{
    QVector<QVector3D> out;

    QVector3D p1 = get000() / Constants::tile_width_pixels;
    QVector3D p2 = get111() / Constants::tile_width_pixels;

    QVector3D start = QVector3D(int(p1.x()),int(p1.y()),int(p1.z()));
    QVector3D end = QVector3D(int(p2.x()),int(p2.y()),int(p2.z()));
    for(int x = start.x(); x <= end.x(); x++){
        for(int y = start.y(); y <= end.y(); y++){
            for(int z = start.z(); z <= end.z(); z++){
                out.append(QVector3D(x,y,z));
            }
        }
    }
    //qDebug()<<start<<end<<"divider"<<out;
    return out;
}



bool Box::isColliding(Box b)
{
    QVector3D v1 = get111() - b.get000();
    QVector3D v2 = get000() - b.get111();

    if(v2.x() < 0 && v2.y() < 0 && v2.z() < 0 && v1.x() > 0 && v1.y() > 0 && v1.z() > 0){
        return true;
    }
    return false;
}

