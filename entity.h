#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>
#include <QVector3D>

#include <world.h>


class Entity
{
public:
    Entity(QVector3D position);

    QVector3D position(){return m_position;}

    void setPosition(QVector3D position);
    void setX(float x){m_position.setX(x);}
    void setY(float y){m_position.setY(y);}
    void setZ(float z){m_position.setZ(z);}
    float x(){return m_position.x();}
    float y(){return m_position.y();}
    float z(){return m_position.z();}

    QVector3D dimensions(){return m_dimensions;}
    void setDimensions(QVector3D dimensions){m_dimensions = dimensions;}
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
    void setRotation(int rotation);
    float width(){return m_dimensions.x();}
    float height(){return m_dimensions.y();}
    float depth(){return m_dimensions.z();}
    int rotation(){return m_rotation;}

    void transform(QVector3D vector);

    void setVelocity(QVector3D vec){m_velocity = vec;}
    void setVelocityX(int x){m_velocity.setX(x);}
    void setVelocityY(int y){m_velocity.setY(y);}
    void setVelocityZ(int z){m_velocity.setZ(z);}
    QVector3D getVelocity(){return m_velocity;}

    void createDetectionBoxPosition (QVector3D newPosition) {m_detectionBoxPosition = newPosition;}
    void createDetectionBoxDimension (QVector3D newDimension) {m_detectionBoxDimension = newDimension;}

    virtual QVector3D currentTile();


    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj);

    void updateDisplay();

protected:

    QVector3D m_position;

    QVector3D m_dimensions;

    QVector3D m_velocity;

    QQuickItem * m_obj = nullptr;


private:
    float m_depth = 0;

    int m_rotation = 0;

    QVector3D m_detectionBoxPosition = QVector3D (0,0,0);
    QVector3D m_detectionBoxDimension = QVector3D (0,0,0);

};

#endif // ENTITY_H
