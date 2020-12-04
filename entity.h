#ifndef ENTITY_H
#define ENTITY_H

#include <QPoint>
#include <QQuickItem>
#include <QVector2D>
#include <QVector3D>

#include <world.h>
#include <unitspace.h>


class Entity
{
public:
    Entity(QVector3D getPosition,World * worldPtr);

    QVector3D getPosition(){return m_position;}

    QVector3D getCenter(){return m_position + m_dimensions/2;}

    void setPosition(QVector3D getPosition);
    void setX(float x){m_position.setX(x);}
    void setY(float y){m_position.setY(y);}
    void setZ(float z){m_position.setZ(z);}
    float x(){return m_position.x();}
    float y(){return m_position.y();}
    float z(){return m_position.z();}

    QVector3D getDimension(){return m_dimensions;}
    void setDimension(QVector3D dimensions){m_dimensions = dimensions;}
    void setWidth(float getWidth);
    void setHeight(float getHeight);
    void setDepth(float getDepth);
    void setRotation(int getRotation);
    float getWidth(){return m_dimensions.x();}
    float getHeight(){return m_dimensions.y();}
    float getDepth(){return m_dimensions.z();}
    int getRotation(){return m_rotation;}

    void transform(QVector3D vector);

    void setVelocity(QVector3D vec){m_velocity = vec;}
    void setVelocityX(int x){m_velocity.setX(x);}
    void setVelocityY(int y){m_velocity.setY(y);}
    void setVelocityZ(int z){m_velocity.setZ(z);}
    QVector3D getVelocity(){return m_velocity;}

    void setDetectionBoxPosition(QVector3D newPosition) {m_detectionBoxPosition = newPosition;}
    void setDetectionBoxDimension(QVector3D newDimension) {m_detectionBoxDimension = newDimension;}
    QVector3D getDetectionBoxPosition(){return m_detectionBoxPosition;}
    QVector3D getDetectionBoxDimension(){return m_detectionBoxDimension;}

    virtual bool detectionBoxPlayerDetection();

    static QVector3D getGlobalPositionFromLocalPosition(QVector3D box_position, QVector3D local_position);

    virtual QVector3D currentTilePosition();
    UnitSpace * getCurrentTile(){return current_space;}
    void setCurrentTile(UnitSpace * space){current_space = space;}

    virtual Entity* getSpecificPtr() {return nullptr;}
    Entity * getEntityPtr(){return this;}


    QQuickItem * getObj(){return m_obj;}
    void assignObj(QQuickItem * obj);

    void updateTilesOccupied() {m_tiles_occupied = World::getTilesOccupied(this);}
    QVector<QVector3D> getTilesOccupied() {return m_tiles_occupied;}

    virtual void iterate();
    virtual void updateDisplay();

protected:
    World * m_worldptr = nullptr;

    UnitSpace * current_space = nullptr;

    QVector3D m_position;

    QVector3D m_dimensions;

    QVector3D m_velocity;

    QQuickItem * m_obj = nullptr;


private:
    float m_depth = 0;

    QVector<QVector3D> m_tiles_occupied = QVector<QVector3D>();

    int m_rotation = 0;

    QVector3D m_detectionBoxPosition = QVector3D (0,0,0);
    QVector3D m_detectionBoxDimension = QVector3D (0,0,0);

};

#endif // ENTITY_H
