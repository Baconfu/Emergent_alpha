#include "box.h"

#include <constants.h>

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

QVector<QVector3D> Box::getOccupiedTiles()
{
    QVector<QVector3D> out;

    QVector3D vector = get111() / Constants::tile_width_pixels - m_position / Constants::tile_width_pixels;
    for(int x = 0; x <= vector.x(); x++){
        for(int y = 0; y <= vector.y(); y++){
            for(int z = 0; z <= vector.z(); z++){
                out.append(m_position/Constants::tile_width_pixels + QVector3D(x,y,z));
            }
        }
    }
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

