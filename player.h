#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QQuickItem>

#include <constants.h>
#include <entity.h>
#include <world.h>


class Player: public Entity
{
public:
    Player(QVector3D getPosition,QQuickItem * obj = nullptr,World * worldptr = nullptr);

    enum direction{
        left = 65,
        up = 87,
        right = 68,
        down = 83,
    };

    enum state{
        in_air = 0,
        below_zero = 1,
        climbing = 2,
    };

    void move(int d);
    void stop(int d);

    void setClimbingState(bool c) {is_climbing = c;}
    bool getClimbingState() {return is_climbing;}
    void setClimbingDirection(int r) {climbing_direction = r;}
    int getClimbingDirection() {return climbing_direction;}

    void setState(int state, bool desired) {
        if (state == in_air) {is_in_air = desired;}
        if (state == below_zero) {is_below_zero = desired;}
        if (state == climbing) {
            if (desired == false){
                setVelocityZ(0);
            }
            is_climbing = desired;
        }
    }

    bool getState(int state){
        if (state == in_air) {return is_in_air;}
        if (state == below_zero) {return is_below_zero;}
        if (state == climbing) {return is_climbing;}
    }

    void updateStates() {
        if (m_position.z() < 0) {setState(below_zero,true);}
    }

    void resolveStates() {
        if(is_below_zero == true){
            setState(climbing,false);
                if (getClimbingDirection() == 0) {setVelocityY(1);}
                if (getClimbingDirection() == 2) {setVelocityY(-1);}
            setPositionZ(0);
            qDebug()<<"below zero is true";
            setState(below_zero,false);
        }
        if(is_climbing == true){

        }
    }

    QVector3D getCurrentTilePosition();


    void iterate();
    void onDetectingEntity(Entity*);
    void onDepartingEntity(Entity*);

    void updateDisplay();

    QPoint getCardinalRotation() {return player_cardinal_rotation;}
    void updatePlayerRotation();

    //QVector<Entity*> getCurrentInteractionEntity() {return current_interaction_entity;}


private:

    //QVector<Entity*> current_interaction_entity = QVector<Entity*> ();

    float travel_speed = 1;
    QPoint player_cardinal_rotation;

    bool is_in_air = false;
    bool is_below_zero = false;
    bool is_climbing = false;
        int climbing_direction = 0;





    void resetAnimCycle();
    void incrementAnimCycle();


};

#endif // PLAYER_H
