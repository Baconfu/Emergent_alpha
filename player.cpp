#include "player.h"

#include <ladder.h>

Player::Player(QVector3D position,QQuickItem * obj,World * worldptr):
    Entity(position,worldptr)
{
    m_obj = obj;
    m_dimensions = QVector3D(20,20,40);
}


void Player::move(int d)
{
    switch(d){
    case left:
        setVelocityX(-1*travel_speed);
        break;
    case right:
        setVelocityX(travel_speed);
        break;
    case up:
        setVelocityY(-1*travel_speed);
        break;
    case down:
        setVelocityY(travel_speed);
        break;
    }
    //case climbing_up;


}

void Player::stop(int d)
{
    switch(d){
    case left:
        if(m_velocity.x() == -travel_speed){
            setVelocityX(0);
        }
        break;
    case right:
        if(m_velocity.x() == travel_speed){
            setVelocityX(0);
        }
        break;
    case up:
        if(m_velocity.y() == -travel_speed){
            setVelocityY(0);
        }
        break;
    case down:
        if(m_velocity.y() == travel_speed){
            setVelocityY(0);
        }
        break;
    }
}

QVector3D Player::currentTilePosition()
{
    return QVector3D(m_position.x() / Constants::tile_width_pixels , m_position.y() / Constants::tile_width_pixels , m_position.z() / Constants::tile_width_pixels);
}

void Player::iterate()
{
    transform(m_velocity);
    if(m_velocity.length() != 0){
        incrementAnimCycle();
        //updateProximalEntities();
        //qDebug()<<getProximalEntities();
    }else{
        resetAnimCycle();
    }

    qDebug()<<getPosition();
    m_obj->setZ(currentTilePosition().y());

    setDetectionBoxPosition(m_position);
    updateDisplay();

}

void Player::interact(Entity* e)
{
    if(typeid (*e) == typeid (Ladder)){
        disableDetection();
        qDebug()<<"detection disabled";
        qDebug()<<getDetectionState();

        QVector3D original_position = m_position;
        qDebug()<<original_position;



        if (m_position.z()<original_position.z()+Constants::tile_width_pixels){
            setVelocity(QVector3D (0,0,1));
            qDebug()<<"rising started";
        }
        if (m_position.z()>original_position.z()+Constants::tile_width_pixels){
            setVelocity(QVector3D (0,0,0));
            qDebug()<<"rising finished!";
        }
        //enableDetection();

    }
}

void Player::updateDisplay()
{
    QVector3D adjust = QVector3D(m_position.x(),m_position.y(),m_position.z() + m_dimensions.z());
    m_obj->setPosition(World::get2DProjection(adjust));

    m_obj->setWidth(World::get2DProjection(m_dimensions).x());

    QVector3D alt = QVector3D(m_dimensions.x(),m_dimensions.y(),m_dimensions.z()*-1);
    m_obj->setHeight(World::get2DProjection(alt).y());

    m_obj->setZ(float(getCenter().y()) / Constants::tile_width_pixels + float(getCenter().z())/100.0/Constants::tile_width_pixels-0.5);
}

void Player::resetAnimCycle()
{
    m_obj->setProperty("anim_cycle",0);
}
void Player::incrementAnimCycle()
{
    m_obj->setProperty("anim_cycle",m_obj->property("anim_cycle").toInt() + 1);
}
