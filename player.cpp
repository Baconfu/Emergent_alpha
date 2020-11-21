#include "player.h"

Player::Player(QQuickItem * parent, QQuickItem * obj):
    Entity(parent)
{
    m_obj = obj;
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

void Player::iterate()
{
    transform(m_velocity.toPoint());
    if(m_velocity.length() != 0){
        incrementAnimCycle();
    }else{
        resetAnimCycle();
    }
}

void Player::resetAnimCycle()
{
    m_obj->setProperty("anim_cycle",0);
}
void Player::incrementAnimCycle()
{
    qDebug()<<m_obj->property("anim_cycle");
    m_obj->setProperty("anim_cycle",m_obj->property("anim_cycle").toInt() + 1);
}
