#ifndef BOX_H
#define BOX_H

#include <QVector3D>

class Box
{
public:
    Box();

    void setPosition(QVector3D position){m_position = position;}
    void setDimensions(QVector3D dimensions){m_dimensions = dimensions;}

    QVector3D position(){return m_position;}
    QVector3D dimensions(){return m_dimensions;}

    int x(){return m_position.x();}
    int y(){return m_position.y();}
    int z(){return m_position.z();}


    QVector3D get000();
    QVector3D get001();
    QVector3D get010();
    QVector3D get011();
    QVector3D get100();
    QVector3D get101();
    QVector3D get110();
    QVector3D get111();




    bool isColliding(Box);

private:
    QVector3D m_position = QVector3D();
    QVector3D m_dimensions = QVector3D();
};

#endif // BOX_H
