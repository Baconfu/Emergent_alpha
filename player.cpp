#include "player.h"

#include <ladder.h>
#include <QTimer>
#include <math.h>

Player::Player():
    Entity()
{

    m_velocity = QVector3D(0,0,0);
    m_acceleration = QVector3D(0,0,-0.1);

    m_mass = 70;
    setContext(detection,true);
}


void Player::move(int d)
{
    /*
    if(getContext(climbing)){

        switch(d){
        case left:
            switch(getRotation()){
            case 0:
                setVelocityX(travel_speed * -1);
                break;
            case 1:
                setVelocityZ(travel_speed * -1);
                break;
            case 2:
                setVelocityX(travel_speed * -1);
                break;
            case 3:
                setVelocityZ(travel_speed);
                break;
            }
            break;
        case right:
            switch(getRotation()){
            case 0:
                setVelocityX(travel_speed);
                break;
            case 1:
                setVelocityZ(travel_speed);
                break;
            case 2:
                setVelocityX(travel_speed);
                break;
            case 3:
                setVelocityZ(travel_speed * -1);
                break;
            }
            break;
        case up:
            switch(getRotation()){
            case 0:
                setVelocityZ(travel_speed);
                qDebug()<<"up";
                break;
            case 1:
                setVelocityX(travel_speed * -1);
                break;
            case 2:
                setVelocityZ(travel_speed * -1);
                break;
            case 3:
                setVelocityX(travel_speed * -1);
                break;
            }
            break;
        case down:
            switch(getRotation()){
            case 0:
                setVelocityZ(travel_speed * -1);
                break;
            case 1:
                setVelocityX(travel_speed);
                break;
            case 2:
                setVelocityZ(travel_speed);
                break;
            case 3:
                setVelocityX(travel_speed);
                break;
            }
            break;
        }
    }
    */
    if(true){
        switch(d){
        case left:
            leftPressed = true;
            setVelocityX(-1*travel_speed);
            setRotation(3);
            break;
        case right:
            rightPressed = true;
            setVelocityX(travel_speed);
            setRotation(1);
            break;
        case up:
            upPressed = true;
            setVelocityY(-1*travel_speed);
            setRotation(0);
            break;
        case down:
            downPressed = true;
            setVelocityY(travel_speed);
            setRotation(2);
            break;
        }
    }



}

void Player::stop(int d)
{
    switch(d){
    case left:
        leftPressed = false;
        if(!rightPressed){
            setVelocityX(0);
        }
        break;
    case right:
        rightPressed = false;
        if(!leftPressed){
            setVelocityX(0);
        }
        break;
    case up:
        upPressed = false;
        if(!downPressed){
            setVelocityY(0);
        }
        /*
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
        }*/
        break;
    case down:
        downPressed = false;
        if(!upPressed){
            setVelocityY(0);
        }
        /*
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
        }*/
        break;

    }
}


void Player::iterate()
{


    if(m_velocity.length() != 0){
        incrementAnimCycle();
    }else{
        resetAnimCycle();
    }

    if (m_acceleration.length() > 0.01){
        if(!getContext(climbing)){
            //setVelocity(getVelocity()+getAcceleration());

        }

    }

    if (m_velocity.length() > 0.01) {
        QVector3D transform = m_velocity;
        if(getContext(climbing)){
            transform.setZ(transform.y() * -1);
            transform.setY(0);
        }
        m_geometry->transform(transform);
    }
    //qDebug()<<m_geometry->position()<<getVelocity()<<getContext(climbing);
    if(m_geometry->position().z() <= 0){
        m_geometry->setZ(0);
        setVelocityZ(0);
    }

    for(int i=0; i<interactingEntities.length(); i++){

        interact(interactingEntities[i]);
    }
    for(int i=0; i<interactingTiles.length(); i++){
        if(interactingTiles[i]->collision_player()){
            qDebug()<<tally<<interactingTiles[i]->position();
            tally+=1;
            collide(interactingTiles[i]->getBox());
        }
    }
    //interactingEntities.clear();

    updateDisplay();

}



void Player::interact(Entity* e)
{

    if(typeid (*e) == typeid (Ladder)){

        if(m_geometry->isColliding(*e->geometry())){
            if(this->getCardinalRotation().x() == e->getCardinalRotation().x() || this->getCardinalRotation().y() == e->getCardinalRotation().y()){
                setAcceleration(QVector3D(0,0,0));
                setContext(climbing,true);
            }
        }else{
            setContext(climbing,false);
            setAcceleration(QVector3D(0,0,-0.1));

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
