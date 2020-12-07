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
    Player* getEntityPtr() {return this;}

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
        Entity::updateContext();

    }

    void resolveContext() {
        Entity::resolveContext();
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
