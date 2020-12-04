#ifndef WORLD_H
#define WORLD_H

#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QRandomGenerator>
#include <QVector>
#include <QString>


#include <paintterrain.h>


//Entity management, player management
//World manages which entities are loaded, and manages player interaction with entities. Also manages visibility of entities.

class Entity;
class Player;
class Chunk;
class Terrain;
class UnitSpace;
class Ladder;
class EntityManager;

class World
{
public:
    World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates);


    void iterate();

    void keyInputs(int event_key);
    void keyRelease(int event_key);

    QVector<Chunk*> getEnvironment(){return environment;}

    static QPointF get2DProjection(QVector3D position);



    void createEntity(QVector3D position, QVector3D dimension, int type, int rotation);

    UnitSpace * getTileFromPixel(QVector3D tile_position);
    static QVector3D getTilePositionFromPixel(QVector3D global_pixel_position);
    static QVector<QVector3D> getTilesOccupied(Entity * entity);

    void registerEntityToTile(QVector3D position, Entity * e);

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
    Chunk * getChunkPtrFromChunkPosition(QPoint chunk_position);


    QPoint getChunkPositionFromTilePosition(QVector3D global_tile_position);
    QVector3D getTilePositionInChunk(QVector3D global_tile_position);

    Chunk * loadChunk(QPoint pos);



    bool chunkAlreadyLoaded(QPoint chunk_position);

    UnitSpace * loadUnitSpace(UnitSpace * space,QVector3D global_space_coordinate,QString type);

    QVector<Entity*> entityList;
    void appendEntity(Entity * e){entityList.append(e);}
    void removeEntity(Entity * e){entityList.removeOne(e);}

    void resolveCollision(Entity * entity,UnitSpace * space);
    void resolveCollision(Entity * entity1, Entity * entity2);

    Player * player = nullptr;

    QPoint player_current_chunk;

    int chunk_size = 100;

    int tile_size = 30;

public:
    QVector<QString> entityIDDictionary;
    void initialiseEntityIDDictionary(){
        for(int i=0; i<1000; i++){
            entityIDDictionary.append("");
        }

        entityIDDictionary[200] = "ladder";
    }


};

#endif // WORLD_H
