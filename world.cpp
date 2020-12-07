#include "world.h"

#include <QElapsedTimer>

#include <constants.h>
#include <entity.h>
#include <player.h>
#include <terrain.h>
#include <testassistant.h>
#include <ladder.h>
#include <entitymanager.h>
#include <math.h>


World::World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates)
{

    gen = QRandomGenerator();

    //Pointers allows <World> to create and draw componenets.
    m_appEngine = engine;
    m_window = window;

    //Root: the root item in the window. Base frame
    root = window->findChild<QQuickItem*>("root");

    //load world from coordinates

    //dev: generate 9 chunks


    /*
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            environment.append(generateChunk(QPoint(i,j)));
        }
    }
    for(int i=0; i<environment.length(); i++){
        environment[i]->writeChunkToFile();
    }*/


    //coordinates should refer to player position upon spawn

    //Initialize player
    chunk_ptr_list.append(loadChunk(QPoint(0,0)));

    initialiseEntityIDDictionary();

    //Creating player
    createEntity(QVector3D (30,90,30),QVector3D (20,20,40),EntityManager::player,0);
    player = dynamic_cast<Player*>(entityList[0]);


    createEntity(QVector3D (30,30,30),QVector3D (30,30,30),EntityManager::ladder,0);
    createEntity(QVector3D (30,30,60),QVector3D (30,30,30),EntityManager::ladder,0);
    createEntity(QVector3D (60,120,30),QVector3D (30,30,30),EntityManager::ladder,2);

    //qDebug()<<"tiles occupied by ladder"<<entityList[0]->getTilesOccupied();
    //qDebug()<<"entities registered to (1,2,0)"<<getTilePtrFromTilePosition(QVector3D(1,2,0))->getEntitiesOnTile();

    /*qDebug()<<"unit position entities:"<<getChunkPtrFromChunkPosition(
                  getChunkPositionFromTilePosition(QVector3D(1,2,0)))
              ->getSpacePtrFromLocalPosition(QVector3D(1,2,0))
              ->getEntitiesOnThisUnitSpace();*/

    //getChunk(getChunkFromTile( global tile position ))->getSpace( getTilePositionInChunk( global tile position ));

}

void World::createEntity(QVector3D position,int type, int rotation)
{

    EntityManager* differentiator = new EntityManager(this);
    Entity* created_entity = differentiator->differentiate(position, dimension, type, rotation);
    created_entity->setCurrentTile(getTilePtrListFromPixel(position));

    created_entity->setPosition(position);
    created_entity->setDimension(dimension);
    created_entity->setRotation(rotation);
    //qDebug()<<created_entity->getRotation();
    created_entity->updateSpacesOccupied();
    //created_entity->updateProximalEntities();
    //qDebug()<<created_entity->getPosition()<<created_entity->getDimension();

    appendEntity(created_entity);

    QString IDString = entityIDDictionary[type];

    QQmlComponent entityComponent(m_appEngine,QUrl("qrc:/"+IDString+".qml"));
    QQuickItem * created_entity_obj = qobject_cast<QQuickItem*>(entityComponent.create());

    created_entity->assignObj(created_entity_obj);
    created_entity_obj->setParentItem(root);
    created_entity_obj->setParent(m_appEngine);

    created_entity_obj->setProperty("m_painted_rotation",rotation);
    created_entity->updateDisplay();

    //qDebug()<<created_entity->getPosition()<<created_entity->getDetectionBoxPosition()<<created_entity->getObj()->z();


}

UnitSpace* World::getTilePtrListFromPixel(QVector3D pixel_position)
{
    QVector3D tile_position = getTilePositionFromPixel(pixel_position);
    Chunk * chunk = getChunkPtrFromChunkPosition(getChunkPositionFromTilePosition(tile_position));
    UnitSpace * space = chunk->getSpacePtrFromLocalTilePosition(getLocalTilePositionFromGlobalPosition(tile_position));
    return space;
}

QVector<UnitSpace *> World::getTilePtrListFromPixel(QVector3D pixel_position, QVector3D other_pixel_position)
{
    QVector<QVector3D> out_position_form;
    float offset = 0.1;

    QVector3D entity_position = pixel_position;
    QVector3D entity_other_dimension = other_pixel_position-QVector3D(offset,offset,offset);


    QVector3D up_left_bottom_tile = getTilePositionFromPixel(entity_position);
    QVector3D down_right_top_tile = getTilePositionFromPixel(entity_other_dimension);


    for (int i = up_left_bottom_tile[0] ; i<(down_right_top_tile[0]+1) ; i++){
        for (int j = up_left_bottom_tile[1] ; j<(down_right_top_tile[1]+1) ; j++){
            for (int k = up_left_bottom_tile[2] ; k<(down_right_top_tile[2]+1) ; k++){
                    out_position_form.append(QVector3D(i,j,k));
            }
        }
    }

    QVector<UnitSpace*> out = QVector<UnitSpace*> ();
    for (int i=0; i<out_position_form.length(); i++){
        out.append(getTilePtrFromTilePosition(out_position_form[i]));
    }

    return out;

}

UnitSpace *World::getTilePtrFromTilePosition(QVector3D tile_position)
{
    Chunk * chunk = getChunkPtrFromChunkPosition(getChunkPositionFromTilePosition(tile_position));
    UnitSpace * space = chunk->getSpacePtrFromLocalTilePosition(getLocalTilePositionFromGlobalPosition(tile_position));
    return space;
}

void World::registerEntityToTile(QVector3D position, Entity* e)
{

    QVector<UnitSpace*> previous_spaces = getTilePtrListFromPixel(e->m_previous_position, e->m_previous_position+e->getDimension());
    QVector<UnitSpace*> new_spaces = getTilePtrListFromPixel(position, position+e->getDimension());

    QVector<Entity*> previous_proximal_entities = QVector<Entity*> ();
    QVector<Entity*> previous_proximal_entities_detection = QVector<Entity*> ();
    QVector<Entity*> now_proximal_entities = QVector<Entity*> ();

    QVector<Entity*> departed_entities = QVector<Entity*> ();

    //Departed entities are calculated based on detection box, not tiles.

    for (int i=0; i<previous_spaces.length(); i++){
        for (int j=0; j<previous_spaces[i]->getEntitiesOnTile().length(); j++){
            previous_proximal_entities.append(previous_spaces[i]->getEntitiesOnTile()[j]);
        }
        previous_spaces[i]->removeEntity(e);
    }
    //qDebug()<<"previous proximal entities regardless collision"<<previous_proximal_entities;

    for (int i=0; i<new_spaces.length(); i++){
        for (int j=0; j<new_spaces[i]->getEntitiesOnTile().length(); j++){
            if (new_spaces[i]->getEntitiesOnTile()[j] == e) {continue;}
            now_proximal_entities.append(new_spaces[i]->getEntitiesOnTile()[j]);
        }
        new_spaces[i]->assignEntity(e);
    }

    if (now_proximal_entities.length() == 0) {departed_entities = previous_proximal_entities; goto a; }
    if (previous_proximal_entities.length() == 0) {departed_entities = QVector<Entity*> (); goto a; }

    //this part only runs if there is stuff in BOTH previous and now tiles

    //calculating which entities have 'departed': i.e. appeared in previous tiles but not now tiles
    for (int i=0; i<previous_proximal_entities.length(); i++){
        if(!now_proximal_entities.contains(previous_proximal_entities[i])){
            departed_entities.append(previous_proximal_entities[i]);
        }
    }

    //calculating which entities are overlapping with the player's detection box previously, but not now
    for (int i=0; i<previous_proximal_entities.length(); i++){
        if (World::detectionBoxOverlapCheck(e,previous_proximal_entities[i]) == false) {
            //previous_proximal_entities_detection.append(previous_proximal_entities[i]);
            departed_entities.append(previous_proximal_entities[i]);
        }
    }
    previous_proximal_entities_detection.removeAll(getPlayerPtr());
    /*qDebug()<<"previous proximal entities in collision now:"<<previous_proximal_entities_detection;

    for (int i=0; i<now_proximal_entities.length(); i++){
        if (World::detectionBoxOverlapCheck(e,now_proximal_entities[i]) == true) {
            previous_proximal_entities_detection.removeOne(now_proximal_entities[i]);\
            qDebug()<<"removed entities since colliding in both times:"<<now_proximal_entities[i];
        }

    }
    qDebug()<<"leftover entities:"<<previous_proximal_entities_detection;

    for (int i=0; i<previous_proximal_entities_detection.length(); i++){
        departed_entities.append(previous_proximal_entities_detection[i]);
    }*/


a:


    departed_entities.removeAll(getPlayerPtr());
    e->updateSpacesOccupied();

    removeDuplicateEntityFromVector(now_proximal_entities);


    e->clearProximalEntities();
    e->removeAllFromProximalEntities(getPlayerPtr());


    //Issue: assigning proximal entites to entity but not used
    for (int i=0; i<now_proximal_entities.length(); i++){
        e->addProximalEntities(now_proximal_entities[i]);
    }

    //executing detection and departure functions for all changed entities

    for(int i=0; i<now_proximal_entities.length(); i++){
        if(e->getContext(Entity::detection)==true &&
            now_proximal_entities[i]->getContext(Entity::detection)==true &&
            detectionBoxOverlapCheck(e,now_proximal_entities[i])==true){
                e->onDetectingEntity(now_proximal_entities[i]);
                now_proximal_entities[i]->onDetectingEntity(e);
            }
    }

    for (int i=0; i<departed_entities.length(); i++){
        departed_entities[i]->onDepartingEntity(e);
        e->onDepartingEntity(departed_entities[i]);
    }

    //qDebug()<<"departed entities:"<<departed_entities;


}

QVector<UnitSpace*> World::getTilesOccupiedPtr(Entity *e)
{
    QVector<UnitSpace*> out;
<<<<<<< HEAD
    QVector<QVector3D> occupied = e->getTilesOccupied();
    for (int i=0; i<occupied.length(); i++){
        out.append(getTilePtrFromTilePosition(occupied[i]));
=======
    for (int i=0; i<e->getOccupiedTilePositions().length(); i++){
        out.append(getTile(e->getOccupiedTilePositions()[i]));
>>>>>>> a20ce3deb0fb8e807179c6fcf358d8e28bcf65af
    }
    return out;
}

void World::removeDuplicateEntityFromVector(QVector<Entity*> v)
{
    for (int i=0; i<v.length(); i++){
        Entity* e = v[i];
        v.removeAll(e);
        v.insert(i,e);
    }
}

bool World::detectionBoxOverlapCheck(Entity *entity_1, Entity *entity_2)
{
    if (entity_2->getDetectionBoxPosition().x()>entity_1->getDetectionBoxDimensionGlobalPosition().x() ||
        entity_1->getDetectionBoxPosition().x()>entity_2->getDetectionBoxDimensionGlobalPosition().x()){
        return false;
    }
    if (entity_2->getDetectionBoxPosition().y()>entity_1->getDetectionBoxDimensionGlobalPosition().y() ||
        entity_1->getDetectionBoxPosition().y()>entity_2->getDetectionBoxDimensionGlobalPosition().y()){
        return false;
    }
    if (entity_2->getDetectionBoxPosition().z()>entity_1->getDetectionBoxDimensionGlobalPosition().z() ||
        entity_1->getDetectionBoxPosition().z()>entity_2->getDetectionBoxDimensionGlobalPosition().z()){
        return false;
    }
    return true;
}



void World::iterate()
{



    //qDebug()<<World::detectionBoxOverlapCheck(player,entityList[0]);

    player->iterate();

    //qDebug()<<"player's graphic z value"<<player->getObj()->z();
    //qDebug()<<"proximal entities player:"<<player->getProximalEntities();
    updateCamera();

    QVector<QPoint> screen_bounds;
    int screen_x = root->property("x").toInt();
    int screen_y = root->property("y").toInt();
    screen_bounds.append(getChunkPositionFromTilePosition(getTilePositionFromPixel(QVector3D(screen_x,screen_y,0))));
    screen_bounds.append(getChunkPositionFromTilePosition(getTilePositionFromPixel(QVector3D(screen_x + root->width(), screen_y,0))));
    screen_bounds.append(getChunkPositionFromTilePosition(getTilePositionFromPixel(QVector3D(screen_x,screen_y + root->height(),0))));
    screen_bounds.append(getChunkPositionFromTilePosition(getTilePositionFromPixel(QVector3D(screen_x + root->width(),screen_y + root->height(),0))));

    for(int i=0; i<screen_bounds.length(); i++){
        if(!chunkAlreadyLoaded(screen_bounds[i])){
            chunk_ptr_list.append(loadChunk(screen_bounds[i]));
        }
    }

    for (int j = 0 ; j<entityList.length() ; j++){
        entityList[j]->iterate();

    }

    QVector<QVector3D> tiles_occupied_by_player = getTilesOccupiedTilePosition(player);

    for(int i=0; i<tiles_occupied_by_player.length(); i++){
        Chunk * chunk = getChunkPtrFromChunkPosition(getChunkPositionFromTilePosition(tiles_occupied_by_player[i]));
        UnitSpace * space = chunk->getSpacePtrFromLocalTilePosition(getLocalTilePositionFromGlobalPosition(tiles_occupied_by_player[i]));

        if(space->collision_player()){
            //qDebug()<<space->position();

            resolveCollision(player,space);
        }

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

int World::index(int i, int j)
{
    return j*Constants::chunk_width_tiles*Constants::world_width_chunks + i;

}

void World::updateCamera()
{

    root->setX(player->getPosition().x()*-1 + root->width()/2);
    root->setY(player->getPosition().y()*-1 + root->height()/2);
}

Chunk *World::generateChunk(QPoint pos)
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

Chunk* World::getChunkPtrFromChunkPosition(QPoint chunk_position)
{
    for(int i=0; i<chunk_ptr_list.length(); i++){
        //environment[i]->getPosition()<<chunk_position;
        if(chunk_ptr_list[i]->getPosition() == chunk_position){
            return chunk_ptr_list[i];
        }
    }
    return nullptr;
}

QVector3D World::getTilePositionFromPixel(QVector3D global_pixel_position)
{
    return QVector3D(int(global_pixel_position.x() / Constants::tile_width_pixels),
                     int(global_pixel_position.y() / Constants::tile_width_pixels),
                     int(global_pixel_position.z() / Constants::tile_width_pixels));
}

QPoint World::getChunkPositionFromTilePosition(QVector3D pos)
{

    QVector3D out = (pos - getLocalTilePositionFromGlobalPosition(pos)) / Constants::chunk_width_tiles;
    //qDebug()<<out<<getTilePositionInChunk(pos)<<pos;
    return QPoint(out.x(),out.y());
}

QVector3D World::getLocalTilePositionFromGlobalPosition(QVector3D pos)
{
    return QVector3D(int(pos.x()) % Constants::chunk_width_tiles,
                     int(pos.y()) % Constants::chunk_width_tiles,
                     pos.z());
}

Chunk *World::loadChunk(QPoint pos)
{
    Chunk * chunk = new Chunk(pos);

    QVector<UnitSpace*> area = chunk->loadChunkFromFile();

    for(int i=0; i<area.length(); i++){
        UnitSpace * u = area[i];
        //qDebug()<<u->position();
        QVector3D pos = QVector3D(chunk->getPosition().x(),chunk->getPosition().y(),0) * Constants::chunk_width_tiles + u->position();
        u->setPosition(pos);
        //qDebug()<<"FINAL POS:"<<pos;
        loadUnitSpaceGraphics(u);

    }

    return chunk;
}

bool World::chunkAlreadyLoaded(QPoint pos)
{
    for(int i=0; i<chunk_ptr_list.length(); i++){
        if(chunk_ptr_list[i]->getPosition() == pos)
            return true;
    }
    return false;
}

void World::loadUnitSpaceGraphics(UnitSpace * space)
{
    QQuickItem * obj;
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

    if(entity->y() + entity->getDimensionY() - 1 > space->y() * Constants::tile_width_pixels && entity->y() + 1 < Constants::tile_width_pixels * (space->y() + space->height())){
        float rightBound = Constants::tile_width_pixels * (space->position().x() + space->width());
        if(entity->x() < rightBound && entity->x() > rightBound - abs(entity->getVelocity().x()) - 1){
            entity->setPositionX(Constants::tile_width_pixels * (space->position().x() + space->width()));
        }
        float leftBound = Constants::tile_width_pixels * space->position().x();
        if(entity->x() + entity->getDimensionX() > leftBound && entity->x() + entity->getDimensionX() < leftBound + abs(entity->getVelocity().x()) + 1){
            entity->setPositionX(Constants::tile_width_pixels * (space->position().x()) - entity->getDimensionX());
        }
    }
    if(entity->x() + entity->getDimensionX() - 1 > space->x() * Constants::tile_width_pixels && entity->x() + 1 < Constants::tile_width_pixels * (space->x() + space->width())){
        float botBound = Constants::tile_width_pixels * (space->position().y() + space->height());
        if(entity->y() < botBound && entity->y() > botBound - abs(entity->getVelocity().y()) - 1){
            entity->setPositionY(Constants::tile_width_pixels * (space->position().y() + space->height()));
        }
        float topBound = Constants::tile_width_pixels * space->position().y();
        if(entity->y() + entity->getDimensionY() > topBound && entity->y() + entity->getDimensionY() < topBound + abs(entity->getVelocity().y()) + 1){
            entity->setPositionY(Constants::tile_width_pixels * (space->position().y()) - entity->getDimensionY());
        }
    }

}

