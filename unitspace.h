#ifndef UNITSPACE_H
#define UNITSPACE_H

#include <QString>
#include <QStringLiteral>
#include <QQuickItem>
#include <QVector3D>

#include <constants.h>
#include <world.h>

class UnitSpace
{
public:
    UnitSpace(QVector3D position);

    virtual bool collision_player() = 0;

    virtual QString type(){return QString();}

    float x(){return m_position.x();}
    float y(){return m_position.y();}
    float z(){return m_position.z();}

    void setX(float x){
        //qDebug()<<"SETX"<<x;
        m_position.setX(x);
    }
    void setY(float y){
        //qDebug()<<"SETY"<<y;
        m_position.setY(y);
    }
    void setZ(float z){
        //qDebug()<<"SETZ"<<z;
        m_position.setZ(z);
    }

    QVector3D dimensions(){return m_dimensions;}
    float width(){return m_dimensions.x();}
    float height(){return m_dimensions.y();}
    float depth(){return m_dimensions.z();}

    void assignEntity(Entity* e){m_entities_on_tile.append(e);}
    void removeEntity(Entity * e){m_entities_on_tile.removeOne(e);}
    QVector<Entity*> getEntitiesOnTile(){return m_entities_on_tile;}

    QVector3D position(){return m_position;}

    void setPosition(QVector3D position);

    void assignObj(QQuickItem * obj);
    QQuickItem * getObj(){return m_obj;}

    void updateDisplay();

protected:
    QVector3D m_position;

    QVector3D m_dimensions = QVector3D(1,1,1);

    QVector<Entity*> m_entities_on_tile;

    QQuickItem * m_obj;

private:
    QVector<Entity*> entityOnUnitspace;
};

#endif // UNITSPACE_H
