#include "world.h"

#include <QElapsedTimer>
#include <QScopedPointer>

#include <constants.h>
#include <entity.h>
#include <player.h>
#include <terrain.h>
#include <testassistant.h>
#include <ladder.h>
#include <entitycreator.h>
#include <math.h>


World::World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates)
{

    gen = QRandomGenerator();

    //Pointers allows <World> to create and draw componenets.
    m_appEngine = engine;
    m_window = window;

    //Root: the root item in the window. Base frame
    root = window->findChild<QQuickItem*>("root");

    entityCreator = new EntityCreator(engine);

    //Creating player
    initialiseEntityIDDictionary();
    Entity * entity = createEntity(EntityCreator::player,QVector3D(0,0,0),0);
    appendEntity(entity);
    player = dynamic_cast<Player*>(entity);


    //-------------------------------------------- below: dev(temporary) -----------------------------------------


    /*
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            environment.append(generateChunk(QPoint(i,j)));
        }
    }
    for(int i=0; i<environment.length(); i++){
        environment[i]->writeChunkToFile();
    }*/

    //Initialize 1st chunk
    chunk_ptr_list.append(loadChunk(QVector3D(0,0,0)));


    entityList.append(createEntity(EntityCreator::ladder,QVector3D(30,60,0),0));

    //entityCreator->createEntity(EntityCreator::ladder);
    //entityCreator->createEntity(EntityCreator::ladder);

    //qDebug()<<"tiles occupied by ladder"<<entityList[0]->getTilesOccupied();
    //qDebug()<<"entities registered to (1,2,0)"<<getTilePtrFromTilePosition(QVector3D(1,2,0))->getEntitiesOnTile();

    /*qDebug()<<"unit position entities:"<<getChunkPtrFromChunkPosition(
                  getChunkPositionFromTilePosition(QVector3D(1,2,0)))
              ->getSpacePtrFromLocalPosition(QVector3D(1,2,0))
              ->getEntitiesOnThisUnitSpace();*/

    //getChunk(getChunkFromTile( global tile position ))->getSpace( getTilePositionInChunk( global tile position ));
}

World::~World()
{
    for(int i=0; i<entityList.length(); i++){
        delete(entityList[i]);
    }
    for(int i=0; i<chunk_ptr_list.length(); i++){
        delete(chunk_ptr_list[i]);
    }
    delete(entityCreator);
}


void World::registerEntityToTile(Entity* entity)
{

    QVector<QVector3D> occupied = entity->geometry()->getOccupiedTiles();
    QVector<UnitSpace*> occupiedTiles;
    for(int i=0; i<occupied.length(); i++){
        occupiedTiles.append(getTile(occupied[i]));
    }

    //qDebug()<<occupied;

    entity->setInteractingTiles(occupiedTiles);

}


void World::iterate()
{
    updateCamera();

    QVector<QVector3D> screen_bounds;
    int screen_x = root->property("x").toInt();
    int screen_y = root->property("y").toInt();
    int screen_z = player->geometry()->z();
    screen_bounds.append(QVector3D(screen_x , screen_y , screen_z ));
    screen_bounds.append(QVector3D(screen_x + root->width() , screen_y , screen_z ));
    screen_bounds.append(QVector3D(screen_x , screen_y + root->height() , screen_z ));
    screen_bounds.append(QVector3D(screen_x + root->width(), screen_y + root->height() , screen_z ));

    for(int i=0; i<screen_bounds.length(); i++){
        if(!chunkAlreadyLoaded(screen_bounds[i] / Constants::tile_width_pixels / Constants::chunk_width_tiles)){
            chunk_ptr_list.append(loadChunk(screen_bounds[i] / Constants::tile_width_pixels / Constants::chunk_width_tiles));
        }
    }


    //The following loops musn't be merged into one loop
    //it is desirable for all entities to iterate before evaluating interactions.

    //Entities iterate

    //remove footprints from previous iteration
    for(int i=0; i<entityList.length(); i++){
        entityList[i]->unregisterFromTiles();
    }
    //add footprints and evaluate entity interactions.
    for(int i=0; i<entityList.length(); i++){
        registerEntityToTile(entityList[i]);
    }
    for (int i = 0 ; i<entityList.length() ; i++){
        entityList[i]->iterate();
    }

}

void World::keyPressed(int event_key)
{
    player->move(event_key);
}

void World::keyRelease(int event_key)
{
    player->stop(event_key);
}

QPointF World::get2DProjection(QVector3D position)
{
    QPointF p;

    p.setX(position.x());

    p.setY(position.y() * sin(1.047) - position.z() * cos(1.047));

    return p;
}

UnitSpace *World::getTile(QVector3D tile_position)
{
    tile_position = QVector3D(int(tile_position.x()),int(tile_position.y()),int(tile_position.z()));
    Chunk * chunk = getChunk(tile_position / Constants::chunk_width_tiles);
    return chunk->getTile(QVector3D(int(tile_position.x()) % Constants::chunk_width_tiles,int(tile_position.y()) % Constants::chunk_width_tiles,int(tile_position.z()) % Constants::chunk_width_tiles));
}

Chunk *World::getChunk(QVector3D chunk_position)
{
    chunk_position = QVector3D(int(chunk_position.x()),int(chunk_position.y()),int(chunk_position.z()));
    for(int i=0; i<chunk_ptr_list.length(); i++){
        if(chunk_ptr_list[i]->getPosition() == chunk_position){
            return chunk_ptr_list[i];
        }
    }
    return nullptr;
}


void World::updateCamera()
{

    root->setX(player->geometry()->position().x()*-1 + root->width()/2);
    root->setY(player->geometry()->position().y()*-1 + root->height()/2);
}

Chunk *World::generateChunk(QVector3D pos)
{
    Chunk * chunk = new Chunk(pos);
    QVector<UnitSpace*> area;
    for(int l=0; l<5; l++){
        int z = l;
        for(int i=0; i<Constants::chunk_width_tiles * Constants::chunk_width_tiles; i++){
            int y = (i - i%Constants::chunk_width_tiles)/Constants::chunk_width_tiles;
            int x = i%Constants::chunk_width_tiles;
            if(z > 0){
                UnitSpace * below = area[(z-1)*Constants::chunk_layer_count_tiles
                        + y*Constants::chunk_width_tiles
                        + x];
                if(typeid (*below) == typeid (Terrain)){
                    if(gen.generate()%100>80){
                        area.append(new Terrain(QVector3D(x,y,z)));
                    }else{
                        area.append(new Air(QVector3D(x,y,z)));
                    }
                }else{
                    area.append(new Air(QVector3D(x,y,z)));
                }
            }
            if(z == 0){
                if(gen.generate()%100>80){

                    area.append(new Terrain(QVector3D(x,y,0)));
                }else{
                    area.append(new Air(QVector3D(x,y,0)));
                }
            }


        }
    }

    chunk->setChunkData(area);
    //qDebug()<<area.length();
    return chunk;
}


Chunk *World::loadChunk(QVector3D pos)
{
    pos = QVector3D(int(pos.x()),int(pos.y()),int(pos.z()));
    Chunk * chunk = new Chunk(pos);

    QVector<UnitSpace*> area = chunk->loadChunkFromFile();

    for(int i=0; i<area.length(); i++){
        loadUnitSpaceGraphics(area[i]);
    }

    return chunk;
}

bool World::chunkAlreadyLoaded(QVector3D pos)
{
    pos = QVector3D(int(pos.x()),int(pos.y()),int(pos.z()));
    for(int i=0; i<chunk_ptr_list.length(); i++){
        if(chunk_ptr_list[i]->getPosition() == pos)
            return true;
    }
    return false;
}

void World::loadUnitSpaceGraphics(UnitSpace * space)
{
    QQuickItem * obj = nullptr;
    if(typeid (*space) == typeid (Terrain)){
        QQmlComponent component(m_appEngine,QUrl("qrc:/terrain.qml"));
        obj = qobject_cast<QQuickItem*>(component.create());
        obj->setParentItem(root);
        obj->setParent(m_appEngine);
        space->assignObj(obj);
        space->updateDisplay();
    }
    if(typeid (*space) == typeid (Air)){
        obj = nullptr;
    }
}



void World::resolveCollision(Entity *entity, UnitSpace *space)
{
    //Potential future use for this function: consider collision behaviour of specific unitspace type.
    entity->collide(space->getBox());

}

Entity *World::createEntity(int type, QVector3D position, int rotation)
{
    Entity * entity = entityCreator->createEntity(type);
    entity->geometry()->setPosition(position);
    entity->setRotation(rotation);

    return entity;

}

