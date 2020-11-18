#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QQuickItem>

#include <entity.h>

class Player: public Entity
{
public:
    Player();

    enum direction{
        left = 0,
        up = 1,
        right = 2,
        down = 3
    };

    void setPosition(QPoint pos) override;

    void move(direction d);
    void stop(direction d);




private:

    float travel_speed = 1;
};

#endif // PLAYER_H
