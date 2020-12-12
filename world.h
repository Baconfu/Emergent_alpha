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
class EntityCreator;

class World
{
public:
    World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates);
    ~World();


    void iterate();

    void keyPressed(int event_key);
    void keyRelease(int event_key);

    QVector<Chunk*> getEnvironment(){return chunk_ptr_list;}

    static QPointF get2DProjection(QVector3D position);

    Player* getPlayerPtr() {return player;}


    UnitSpace* getTile(QVector3D tile_position);
    Chunk* getChunk(QVector3D chunk_position);

    void registerEntityToTile(Entity * e);

    QVector<QString> entityIDDictionary;
    void initialiseEntityIDDictionary(){
        for(int i=0; i<1000; i++){
            entityIDDictionary.append("");
        }

        entityIDDictionary[200] = "ladder";
        entityIDDictionary[999] = "player";
    }

private:
    //Debug tools
    int tally = 0;
    //end: Debug tools

    //important pointers
    QRandomGenerator gen;

    QQmlApplicationEngine * m_appEngine = nullptr;
    QQuickWindow * m_window = nullptr;
    QQuickItem * root = nullptr;

    EntityCreator * entityCreator = nullptr;
    Player* player = nullptr;

    void updateCamera();


    //chunk management
    QVector<Chunk*> chunk_ptr_list;

    Chunk * generateChunk(QVector3D pos);
    Chunk * loadChunk(QVector3D pos);
    bool chunkAlreadyLoaded(QVector3D chunk_position);




    void loadUnitSpaceGraphics(UnitSpace * space);

    QVector<Entity*> entityList;
    void appendEntity(Entity * e){entityList.append(e);}
    void removeEntity(Entity * e){entityList.removeOne(e);}

    void resolveCollision(Entity * entity,UnitSpace * space);
    void resolveCollision(Entity * entity1, Entity * entity2);


    Entity * createEntity(int type,QVector3D position,int rotation);


    QPoint player_current_chunk;



};

#endif // WORLD_H
