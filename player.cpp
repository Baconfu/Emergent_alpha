#include "player.h"

#include <ladder.h>
#include <QTimer>
#include <math.h>

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
        setRotation(3);
        break;
    case right:
        setVelocityX(travel_speed);
        setRotation(1);
        break;
    case up:
        if(is_climbing == false){
            setVelocityY(-1*travel_speed);
            setRotation(0);
        }
        if(is_climbing == true) {
            if(climbing_direction == 0) {setVelocityZ(travel_speed);}

            if(climbing_direction == 2) {setVelocityZ(-1*travel_speed);}
        }
        break;
    case down:
        if(is_climbing == false){
            setVelocityY(travel_speed);
            setRotation(2);
        }
        if(is_climbing == true) {
            if(climbing_direction == 0) {setVelocityZ(-1*travel_speed);}

            if(climbing_direction == 2) {setVelocityZ(travel_speed);}
        }
        break;
    }


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
        if(is_climbing == false){
            if(m_velocity.y() == -travel_speed){
                setVelocityY(0);
                break;
            }
        }
        if(is_climbing == true) {
            if(m_velocity.z() == abs(travel_speed)){
                setVelocityZ(0);
                break;
            }
        }
        break;
    case down:
        if(is_climbing == false){
            if(m_velocity.y() == travel_speed){
                setVelocityY(0);
                break;
            }
        }
        if(is_climbing == true) {
            if(m_velocity.z() == abs(travel_speed)){
                setVelocityZ(0);
                break;
            }
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
    qDebug()<<m_velocity;

    if(m_velocity.length() != 0){
        incrementAnimCycle();
        //updateProximalEntities();
        //qDebug()<<getProximalEntities();
    }else{
        resetAnimCycle();
    }

    //qDebug()<<getPosition();
    m_obj->setZ(currentTilePosition().y());

    setDetectionBoxPosition(m_position);
    updateDisplay();

}

void Player::onDetectingEntity(Entity* e)
{

    if(typeid (*e) == typeid (Ladder)){
        if(getRotation() == e->getRotation()){
            resetVelocity();
            qDebug()<<"interacted with ladder"<<e;
            setVelocityZ(1);
            disableDetection();
            setClimbingState(true);
            setClimbingDirection(e->getRotation());
        }

    }
}

void Player::onDepartingEntity(Entity* e){

    if(typeid (*e) == typeid (Ladder) && getClimbingState()==true){
        setVelocityZ(0);
        if (climbing_direction == 0) {setVelocityY(-1);}

        if (climbing_direction == 2) {setVelocityY(1);}

        setClimbingState(false);

        qDebug()<<"left the ladder";
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
