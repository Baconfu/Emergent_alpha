#include "player.h"

#include <ladder.h>
#include <QTimer>
#include <math.h>

Player::Player():
    Entity()
{

    m_velocity = QVector3D(0,0,0);
    m_acceleration = QVector3D(0,0,0);

    m_mass = 70;
    setContext(detection,true);
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
        if(getContext(climbing) == false){
            setVelocityY(-1*travel_speed);
            setRotation(0);
        }
        if(getContext(climbing) == true) {
            if(getRotation() == 0) {setVelocityZ(travel_speed);}

            if(getRotation() == 2) {setVelocityZ(-1*travel_speed);}
        }
        break;
    case down:
        if(getContext(climbing) == false){
            setVelocityY(travel_speed);
            setRotation(2);
        }
        if(getContext(climbing) == true) {
            if(getRotation() == 0) {setVelocityZ(-1*travel_speed);}

            if(getRotation() == 2) {setVelocityZ(travel_speed);}
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
        if(getContext(climbing) == false){
            if(m_velocity.y() == -travel_speed){
                setVelocityY(0);
                break;
            }
        }
        if(getContext(climbing) == true) {
            if(m_velocity.z() == travel_speed){
                setVelocityZ(0);
                break;
            }
        }
        break;
    case down:
        if(getContext(climbing) == false){
            if(m_velocity.y() == travel_speed){
                setVelocityY(0);
                break;
            }
        }
        if(getContext(climbing) == true) {
            if(m_velocity.z() == travel_speed){
                setVelocityZ(0);
                break;
            }
        }
        break;

    }
}

void Player::iterate()
{


    //qDebug()<<"player velocity"<<m_velocity;
    //qDebug()<<"player rotation"<<player_cardinal_rotation;

    if (m_acceleration.length() > 0.01){
        //setVelocity(getVelocity()+getAcceleration());
    }
    if (m_velocity.length() > 0.01) {
        m_geometry->transform(m_velocity);
    }

    if(m_velocity.length() != 0){
        incrementAnimCycle();
    }else{
        resetAnimCycle();
    }


    updateDisplay();
}



void Player::interact(Entity* e)
{
    //qDebug()<<"detected"<<e;
    if(typeid (*e) == typeid (Ladder)){
        if(collide(*e->geometry())){
            if(this->getCardinalRotation().x() == e->getCardinalRotation().x() || this->getCardinalRotation().y() == e->getCardinalRotation().y()){
                setAcceleration(QVector3D(0,0,0));
                setContext(climbing,true);
            }
        }
    }
}


void Player::resetAnimCycle()
{
    m_obj->setProperty("anim_cycle",0);
}
void Player::incrementAnimCycle()
{
    m_obj->setProperty("anim_cycle",m_obj->property("anim_cycle").toInt() + 1);
}
