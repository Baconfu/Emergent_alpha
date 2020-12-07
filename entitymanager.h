#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QQmlApplicationEngine>
#include <QString>


#include <entity.h>
#include <ladder.h>
#include <player.h>
#include <world.h>

class EntityManager
{
public:
    EntityManager(World * worldptr);
    Entity* differentiate(QVector3D position, QVector3D dimension, int type, int rotation);

    /*initial idea of item id:
     * 1xx: building
     * 2xx: traversable
     * 3xx: decoratives
     * 8xx: obstacles
     *
     */


    enum entityID {
        air = 0,
        ladder = 200,
        player = 999,
    };

    Entity* differentiateToLadder(QVector3D position, QVector3D dimension, int rotation);
    Entity* differentiateToPlayer(QVector3D position);

private:
    QQmlApplicationEngine * m_appEngine = nullptr;

    World * m_worldptr = nullptr;

};

#endif // ENTITYMANAGER_H
