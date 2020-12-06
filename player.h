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

    void move(int d);
    void stop(int d);

    void setClimbingDirection(int r) {climbing_direction = r;}
    int getClimbingDirection() {return climbing_direction;}

    void setContext(int state, bool desired) {
        Entity::setContext(state,desired);
        if (state == climbing) {
            if (desired == false){
                setVelocityZ(0);
            }
        }
    }

    void updateContext() {
        if (m_position.z() < 0) {setContext(below_zero,true);}
    }

    void resolveContext() {
        if(getContext(below_zero) == true){
            setContext(climbing,false);
            setContext(below_zero,false);
                if (getClimbingDirection() == 0) {setVelocityY(1);}
                if (getClimbingDirection() == 2) {setVelocityY(-1);}
            setPositionZ(0);            
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

    int climbing_direction = 0;





    void resetAnimCycle();
    void incrementAnimCycle();


};

#endif // PLAYER_H
