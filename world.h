#ifndef WORLD_H
#define WORLD_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QRandomGenerator>
#include <QVector>


#include <paintterrain.h>


//Entity management, player management
//World manages which entities are loaded, and manages player interaction with entities. Also manages visibility of entities.

class Entity;
class Player;
class Chunk;
class Terrain;
class UnitSpace;

class World
{
public:
    World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates);


    void iterate();

    void keyInputs(int event_key);
    void keyRelease(int event_key);

    QVector<Chunk*> getEnvironment(){return environment;}

    static QPointF get2DProjection(QVector3D position);

private:
    int tally = 0;
    QRandomGenerator gen;

    int screen_width_tiles = 640 / 30;
    int screen_height_tiles = 480 / 26;



    int index(int i,int j);

    QQmlApplicationEngine * m_appEngine = nullptr;
    QQuickWindow * m_window = nullptr;
    QQuickItem * root = nullptr;

    void updateCamera();

    Chunk * generateChunk(QPoint pos);

    QVector<Chunk*> environment;
    Chunk * getChunk(QPoint chunk_position);

    QVector3D getTileFromPixel(QVector3D global_pixel_position);
    QPoint getChunkFromTile(QVector3D global_tile_position);
    QVector3D getTilePositionInChunk(QVector3D global_tile_position);

    Chunk * loadChunk(QPoint pos);

    QVector<QVector3D> tilesOccupied(Entity * entity);

    bool chunkAlreadyLoaded(QPoint chunk_position);

    UnitSpace * loadUnitSpace(UnitSpace * space,QVector3D global_space_coordinate,QString type);

    QVector<Entity*> entities;
    void appendEntity(Entity * e){entities.append(e);}
    void removeEntity(Entity * e){entities.removeOne(e);}

    void resolveCollision(Entity * entity,UnitSpace * space);

    Player * player = nullptr;

    QPoint player_current_chunk;

    int chunk_size = 100;

    int tile_size = 30;

};

#endif // WORLD_H
