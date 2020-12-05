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

    void setClimbingState(bool c) {is_climbing = c;}
    bool getClimbingState() {return is_climbing;}
    void setClimbingDirection(int r) {climbing_direction = r;}
    int getClimbingDirection() {return climbing_direction;}

    QVector3D currentTilePosition();


    void iterate();
    void onDetectingEntity(Entity*);
    void onDepartingEntity(Entity*);

    void updateDisplay();



    //QVector<Entity*> getCurrentInteractionEntity() {return current_interaction_entity;}


private:

    //QVector<Entity*> current_interaction_entity = QVector<Entity*> ();

    float travel_speed = 1;

    bool is_climbing = false;
    int climbing_direction = 0;

    void resetAnimCycle();
    void incrementAnimCycle();


};

#endif // PLAYER_H
