#ifndef WORLD_H
#define WORLD_H

#include <QVector>

#include <entity.h>
#include <player.h>

class World
{
public:
    World(QPoint coordinates);


    void iterate();

    void keyInputs(int event_key);
    void keyRelease(int event_key);

private:



    QVector<Entity*> entities;

    Player * player = nullptr;


};

#endif // WORLD_H
