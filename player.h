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
    Player();
    Player* getEntityPtr() {return this;}

    enum direction{
        left = 65,
        up = 87,
        right = 68,
        down = 83,
    };

    void move(int d);
    void stop(int d);

    void setContext(int state, bool desired) {
        Entity::setContext(state,desired);
        if (state == climbing) {
            if (desired == false){
                setVelocityZ(0);
            }
        }
    }


    void iterate();

    void interact(Entity*);


private:


    float travel_speed = 1;

    void resetAnimCycle();
    void incrementAnimCycle();


};

#endif // PLAYER_H
