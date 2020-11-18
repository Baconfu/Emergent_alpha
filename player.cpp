#include "player.h"

Player::Player()
{

}

void Player::setPosition(QPoint pos)
{

}

void Player::move(Player::direction d)
{
    switch(d){
    case left:
        setVelocityX(-1*travel_speed);
    case right:
        setVelocityX(travel_speed);
    case up:
        setVelocityY(-1*travel_speed);
    case down:
        setVelocityY(travel_speed);
    }
}

void Player::stop(Player::direction d)
{
    switch(d){
    case left:
        if(m_velocity.x() == -travel_speed){
            setVelocityX(0);
        }
    case right:
        if(m_velocity.x() == travel_speed){
            setVelocityX(0);
        }
    case up:
        if(m_velocity.y() == -travel_speed){
            setVelocityY(0);
        }
    case down:
        if(m_velocity.y() == travel_speed){
            setVelocityY(0);
        }
    }
}
