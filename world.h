#ifndef WORLD_H
#define WORLD_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QVector>


#include <chunk.h>
#include <coordinate.h>
#include <entity.h>
#include <player.h>
#include <terrain.h>
#include <paintterrain.h>
#include <unitspace.h>

//Entity management, player management
//World manages which entities are loaded, and manages player interaction with entities. Also manages visibility of entities.

class World
{
public:
    World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates);


    void iterate();

    void keyInputs(int event_key);
    void keyRelease(int event_key);

    QVector<Chunk*> getEnvironment(){return environment;}

private:

    int screen_width_tiles = 640 / 30;
    int screen_height_tiles = 480 / 26;


    QQmlApplicationEngine * m_appEngine = nullptr;
    QQuickWindow * m_window = nullptr;
    QQuickItem * root = nullptr;

    QVector<Chunk*> environment;
    QPoint getCurrentChunk(QPoint pos);
    QPoint getPositionInChunk(QPoint pos);
    Chunk * loadChunk(QPoint pos);

    bool chunkAlreadyLoaded(QPoint pos);

    UnitSpace * loadUnitSpace(Coordinate c);

    QVector<Entity*> entities;
    void appendEntity(Entity * e){entities.append(e);}
    void removeEntity(Entity * e){entities.removeOne(e);}

    Player * player = nullptr;

    int chunk_size = 100;

    int tile_size = 30;

};

#endif // WORLD_H
