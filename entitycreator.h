#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <QQmlApplicationEngine>
#include <QString>


#include <entity.h>
#include <ladder.h>
#include <player.h>

class EntityCreator
{
public:
    EntityCreator(QQmlApplicationEngine * appEngine);
    Entity* createEntity(int type);

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



private:
    QQmlApplicationEngine * m_appEngine = nullptr;

    Entity* createLadder();
    Entity* createPlayer();

};

#endif // ENTITYMANAGER_H
