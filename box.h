#ifndef BOX_H
#define BOX_H

#include <QVector>
#include <QVector3D>

class Box
{
public:
    Box();

    void setPosition(QVector3D position){m_position = position;}
    void transform(QVector3D vector){m_position += vector;}
    void setDimensions(QVector3D dimensions){m_dimensions = dimensions;}

    void setX(float x){m_position.setX(x);}
    void setY(float y){m_position.setY(y);}
    void setZ(float z){m_position.setZ(z);}

    QVector3D position(){return m_position;}
    QVector3D dimensions(){return m_dimensions;}

    float x(){return m_position.x();}
    float y(){return m_position.y();}
    float z(){return m_position.z();}

    float width(){return m_dimensions.x();}
    float height(){return m_dimensions.y();}
    float depth(){return m_dimensions.z();}


    QVector3D get000();
    QVector3D get001();
    QVector3D get010();
    QVector3D get011();
    QVector3D get100();
    QVector3D get101();
    QVector3D get110();
    QVector3D get111();

    void rotate();


    QVector<QVector3D> getOccupiedTiles();


    bool isColliding(Box);

private:
    int rotation = 0;
    QVector3D m_position = QVector3D(0,0,0);
    QVector3D m_dimensions = QVector3D(0,0,0);
};

#endif // BOX_H
