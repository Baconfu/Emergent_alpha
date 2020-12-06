#include "player.h"

#include <ladder.h>
#include <QTimer>
#include <math.h>

Player::Player(QVector3D position,QQuickItem * obj,World * worldptr):
    Entity(position,worldptr)
{
    m_obj = obj;
    m_dimensions = QVector3D(20,20,40);
    setDetectionBoxDimension(QVector3D(m_dimensions.x(),m_dimensions.y(),m_dimensions.z()+1));
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

QVector3D Player::getCurrentTilePosition()
{
    return QVector3D(m_position.x() / Constants::tile_width_pixels , m_position.y() / Constants::tile_width_pixels , m_position.z() / Constants::tile_width_pixels);
}

void Player::iterate()
{
    transform(m_velocity);
    updatePlayerRotation();
    updateStates();
    resolveStates();

    qDebug()<<"player velocity"<<m_velocity;
    qDebug()<<"player rotation"<<player_cardinal_rotation;

    if(m_velocity.length() != 0){
        incrementAnimCycle();
        //updateProximalEntities();
        //qDebug()<<getProximalEntities();
    }else{
        resetAnimCycle();
    }



    qDebug()<<"player position"<<getPosition();
    qDebug()<<"player detection state"<<getDetectionState();
    m_obj->setZ(getCurrentTilePosition().y());

    setDetectionBoxPosition(QVector3D(m_position.x(),m_position.y(),m_position.z()-1));

    updateDisplay();

}

void Player::interactWith(Entity * e2)
{
    if(typeid (*e2) == typeid (Ladder)){
        setState(is_climbing,true);
    }
}

void Player::onDetectingEntity(Entity* e)
{
    qDebug()<<"detected"<<e;
    if(typeid (*e) == typeid (Ladder)){
        if(this->getCardinalRotation().x() == e->getCardinalRotation().x() ||
           this->getCardinalRotation().y() == e->getCardinalRotation().y()){
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

    if(typeid (*e) == typeid (Ladder)){

        enableDetection();

            if (getClimbingState() == true){

            setVelocityZ(0);
            if (climbing_direction == 0) {
                qDebug()<<"triggered nudge";
                if (getCardinalRotation().y()==-1 || getRotation()==0) {setVelocityY(-1*travel_speed);}

                if (getCardinalRotation().x()==1 || getRotation()==2) {setVelocityX(travel_speed);}

            }

            if (climbing_direction == 2) {setVelocityY(1);}

            setClimbingState(false);

            qDebug()<<"left the ladder";
        }
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

void Player::updatePlayerRotation()
{
    player_cardinal_rotation = QPoint(getVelocity().x()/travel_speed,getVelocity().y()/travel_speed);
}

void Player::resetAnimCycle()
{
    m_obj->setProperty("anim_cycle",0);
}
void Player::incrementAnimCycle()
{
    m_obj->setProperty("anim_cycle",m_obj->property("anim_cycle").toInt() + 1);
}
