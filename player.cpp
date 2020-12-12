#include "player.h"

Player::Player(QVector3D position,QQuickItem * obj):
    Entity(position)
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

QVector3D Player::currentTile()
{
    return QVector3D(m_position.x() / Constants::tile_width_pixels , m_position.y() / Constants::tile_width_pixels , m_position.z() / Constants::tile_width_pixels);
}

void Player::iterate()
{
    transform(m_velocity);
    if(m_velocity.length() != 0){
        incrementAnimCycle();
    }else{
        resetAnimCycle();
    }
    m_obj->setZ(currentTile().y());
    updateDisplay();
}

void Player::resetAnimCycle()
{
    m_obj->setProperty("anim_cycle",0);
}
void Player::incrementAnimCycle()
{
    m_obj->setProperty("anim_cycle",m_obj->property("anim_cycle").toInt() + 1);
}
