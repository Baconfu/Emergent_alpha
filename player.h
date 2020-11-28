#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QQuickItem>

#include <constants.h>
#include <entity.h>


class Player: public Entity
{
public:
    Player(QVector3D position,QQuickItem * obj = nullptr);

    enum direction{
        left = 65,
        up = 87,
        right = 68,
        down = 83
    };

    void move(int d);
    void stop(int d);

    QVector3D currentTile();


    void iterate();


private:

    float travel_speed = 1;

    void resetAnimCycle();
    void incrementAnimCycle();
};

#endif // PLAYER_H
