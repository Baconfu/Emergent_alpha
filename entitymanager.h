#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QQmlApplicationEngine>
#include <QString>


#include <entity.h>
#include <ladder.h>
#include <player.h>

class EntityManager
{
public:
    EntityManager();
    Entity* differentiate(QVector3D position, int type, int rotation);

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

    Entity* differentiateToLadder(QVector3D position, int rotation);
    Entity* differentiateToPlayer(QVector3D position);

private:
    QQmlApplicationEngine * m_appEngine = nullptr;

};

#endif // ENTITYMANAGER_H
