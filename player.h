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
        down = 83
    };

    void move(int d);
    void stop(int d);

    QVector3D currentTilePosition();

    QString getTypeName(){return "player";}


    void iterate();

    void updateDisplay();

private:



    float travel_speed = 1;

    void resetAnimCycle();
    void incrementAnimCycle();
};

#endif // PLAYER_H
