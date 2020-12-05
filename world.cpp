#include "world.h"


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

    QVector3D initialPlayerPosition = QVector3D(0,0,0);
    QVector3D initialPlayerDimension = QVector3D(Constants::player_width_pixels,Constants::player_width_pixels,Constants::player_height_pixels);
    player = new Player(initialPlayerPosition,nullptr,this);


    //Creating player avatar graphics
    QQmlComponent component(engine,QUrl("qrc:/playerAvatar.qml"));
    QQuickItem * obj = qobject_cast<QQuickItem*>(component.create());
    //Parenting graphics item to player
    obj->setParentItem(root);
    obj->setParent(engine);
    player->assignObj(obj);


    player->setDimension(initialPlayerDimension);
    player->setDetectionBoxPosition(initialPlayerPosition);
    player->setDetectionBoxDimension(initialPlayerDimension);

    qDebug()<<player->getDetectionBoxPosition()<<player->getDetectionBoxDimensionGlobalPosition();

    player->updateDisplay();
    player->setCurrentTile(getTilePtrFromPixel(initialPlayerPosition));



    initialiseEntityIDDictionary();

    //qDebug()<<"player initialised";

    createEntity(QVector3D (30,60,0),QVector3D (30,30,30),EntityManager::ladder,0);
    createEntity(QVector3D (30,60,30),QVector3D (30,30,30),EntityManager::ladder,0);
    createEntity(QVector3D (30,120,0),QVector3D (30,30,30),EntityManager::ladder,2);

    qDebug()<<"tiles occupied by ladder"<<entityList[0]->getTilesOccupied();
    qDebug()<<"entities registered to (1,2,0)"<<getTilePtrFromTilePosition(QVector3D(1,2,0))->getEntitiesOnTile();

    /*qDebug()<<"unit position entities:"<<getChunkPtrFromChunkPosition(
                  getChunkPositionFromTilePosition(QVector3D(1,2,0)))
              ->getSpacePtrFromLocalPosition(QVector3D(1,2,0))
              ->getEntitiesOnThisUnitSpace();*/

    //getChunk(getChunkFromTile( global tile position ))->getSpace( getTilePositionInChunk( global tile position ));

}

void World::createEntity(QVector3D position,QVector3D dimension,int type, int rotation)
{

    EntityManager* differentiator = new EntityManager(this);
    Entity* created_entity = differentiator->differentiate(position, dimension, type, rotation);
    created_entity->setCurrentTile(getTilePtrFromPixel(position));

    created_entity->setPosition(position);
    created_entity->setDimension(dimension);
    created_entity->setRotation(rotation);
    //qDebug()<<created_entity->getRotation();
    created_entity->updateTilesOccupied();
    //created_entity->updateProximalEntities();
    qDebug()<<created_entity->getPosition()<<created_entity->getDimension();


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

UnitSpace* World::getTilePtrFromPixel(QVector3D pixel_position)
{
    QVector3D tile_position = getTilePositionFromPixel(pixel_position);
    Chunk * chunk = getChunkPtrFromChunkPosition(getChunkPositionFromTilePosition(tile_position));
    UnitSpace * space = chunk->getSpacePtrFromLocalTilePosition(getLocalTilePositionFromGlobalPosition(tile_position));
    return space;
}

QVector<UnitSpace *> World::getTilePtrFromPixel(QVector3D pixel_position, QVector3D dimension)
{
    QVector<QVector3D> out_position_form;
    float offset = 0.1;

    QVector3D entity_position = pixel_position;
    QVector3D entity_dimension = dimension-QVector3D(offset,offset,offset);


    QVector3D up_left_bottom_tile = getTilePositionFromPixel(entity_position);
    QVector3D down_right_top_tile = getTilePositionFromPixel(entity_position + entity_dimension);


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
    QVector<UnitSpace*> previous_spaces = getTilePtrFromPixel(e->m_previous_position, e->getDimension());
    QVector<UnitSpace*> new_spaces = getTilePtrFromPixel(position, e->getDimension());
    QVector<Entity*> previous_proximal_entities = QVector<Entity*> ();
    QVector<Entity*> new_proximal_entities = QVector<Entity*> ();
    QVector<Entity*> departed_entities = QVector<Entity*> ();

    for (int i=0; i<previous_spaces.length(); i++){
        previous_spaces[i]->removeEntity(e);
        for (int j=0; j<previous_spaces[i]->getEntitiesOnTile().length(); j++){
            previous_proximal_entities.append(previous_spaces[i]->getEntitiesOnTile()[j]);
        }
    }

    for (int i=0; i<new_spaces.length(); i++){
        for (int j=0; j<new_spaces[i]->getEntitiesOnTile().length(); j++){
            if (new_spaces[i]->getEntitiesOnTile()[j] == e) {continue;}
            new_proximal_entities.append(new_spaces[i]->getEntitiesOnTile()[j]);
        }
        new_spaces[i]->assignEntity(e);
    }

    //QVector<Entity*> intersection = QVector<Entity*> ();
    //std::set_intersection(previous_proximal_entities.begin(),previous_proximal_entities.end(),new_proximal_entities.begin(),new_proximal_entities.end(),intersection);
    //std::set_difference(previous_proximal_entities.begin(),previous_proximal_entities.end(),new_proximal_entities.begin(),new_proximal_entities.end(),departed_entities);

    if (new_proximal_entities.length() == 0) {departed_entities = previous_proximal_entities; qDebug()<<"no new entities"; goto a; }
    if (previous_proximal_entities.length() == 0) {departed_entities = QVector<Entity*> (); qDebug()<<"previous no entities"; goto a; }

    for (int i=0; i<previous_proximal_entities.length(); i++){
        bool included = false;
        for (int j=0; j<new_proximal_entities.length(); j++){
            if (previous_proximal_entities[i] == new_proximal_entities[j]) {included = true; break;};
        }
        if (included == false) {departed_entities.append(previous_proximal_entities[i]);}
    }

a:
    departed_entities.removeAll(getPlayerPtr());
    e->updateTilesOccupied();


    //qDebug()<<"old spaces:"<<previous_spaces;
    //qDebug()<<"new spaces:"<<new_spaces;
    //qDebug()<<e->m_previous_position<<e->getDimension();
    //removeDuplicateEntityFromVector(new_proximal_entities);




    e->clearProximalEntities();
    e->removeAllFromProximalEntities(getPlayerPtr());

    for (int i=0; i<new_proximal_entities.length(); i++){
        e->addProximalEntities(new_proximal_entities[i]);
    }

    for(int i=0; i<new_proximal_entities.length(); i++){
        if(e->getDetectionState()==true &&
            new_proximal_entities[i]->getDetectionState()==true &&
            detectionBoxOverlapCheck(e,new_proximal_entities[i])==true){
                e->onDetectingEntity(new_proximal_entities[i]);
                new_proximal_entities[i]->onDetectingEntity(e);
                qDebug()<<"collision triggered";
            }
    }

    for (int i=0; i<departed_entities.length(); i++){
        if (true){
        departed_entities[i]->onDepartingEntity(e);
        e->onDepartingEntity(departed_entities[i]);
        }
    }
    //qDebug()<<space->position();
    //qDebug()<<space->getEntitiesOnThisUnitSpace();
    qDebug()<<"departed entities:"<<departed_entities;

}

QVector<UnitSpace*> World::getTilesOccupiedPtr(Entity *e)
{
    QVector<UnitSpace*> out;
    for (int i=0; i<e->getTilesOccupied().length(); i++){
        out.append(getTilePtrFromTilePosition(e->getTilesOccupied()[i]));
    }
    return out;
}

void World::removeDuplicateEntityFromVector(QVector<Entity*> v)
{
    for (int i=0; i<v.length(); i++){
        Entity* e = v[i];
        v.removeAll(v[i]);
        v.insert(i,e);
    }



    /*QVector<int> redundant_index;

    for (int i=0; i<v.length(); i++){
        for (int j=i+1; j<v.length(); j++){
            if (v[i] == v[j]){
                redundant_index.append(i);
            }
        }
    }

    std::sort (redundant_index.begin(), redundant_index.end());
    std::reverse (redundant_index.begin(), redundant_index.end());
    for (int i=0; i<redundant_index.length(); i++){
        v.remove(redundant_index[i]);
    }*/
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
    for (int j = 0 ; j<entityList.length() ; j++){
        entityList[j]->iterate();
    }

    //qDebug()<<World::detectionBoxOverlapCheck(player,entityList[0]);

    player->iterate();

    //qDebug()<<"player's graphic z value"<<player->getObj()->z();
    qDebug()<<"proximal entities player:"<<player->getProximalEntities();
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


    QVector<QVector3D> tiles_occupied_by_player = getTilesOccupiedPosition(player);

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
    qDebug()<<area.length();
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
    int w = Constants::chunk_width_tiles;

    int count = 0;
    int total = 0;

    for(int i=0; i<area.length(); i++){
        UnitSpace * u = area[i];
        //qDebug()<<u->position();
        QVector3D pos = QVector3D(chunk->getPosition().x(),chunk->getPosition().y(),0) * Constants::chunk_width_tiles + u->position();
        //qDebug()<<"FINAL POS:"<<pos;
        total+=1;
        if(typeid (*u) == typeid (Air)){
            loadUnitSpace(u,pos,"air");
        }else{
            loadUnitSpace(u,pos,"terrain");
            count+=1;

            /*
            if(gen.generate()%10 > 6){
                loadUnitSpace(u,pos+QVector3D(0,0,1),"terrain");
                if(gen.generate()%10 > 6){
                    loadUnitSpace(u,pos+QVector3D(0,0,2),"terrain");
                }
            }*/

        }
    }

    return chunk;
}

QVector<QVector3D> World::getTilesOccupiedPosition(Entity* entity)
{
    QVector<QVector3D> out;
    float offset = 0.1;

    QVector3D entity_position = entity->getPosition();
    QVector3D entity_dimension = entity->getDimension()-QVector3D(offset,offset,offset);


    QVector3D up_left_bottom_tile = getTilePositionFromPixel(entity_position);
    QVector3D down_right_top_tile = getTilePositionFromPixel(entity_position + entity_dimension);


    for (int i = up_left_bottom_tile[0] ; i<(down_right_top_tile[0]+1) ; i++){
        for (int j = up_left_bottom_tile[1] ; j<(down_right_top_tile[1]+1) ; j++){
            for (int k = up_left_bottom_tile[2] ; k<(down_right_top_tile[2]+1) ; k++){
                    out.append(QVector3D(i,j,k));
            }
        }
    }

    return out;


}

bool World::chunkAlreadyLoaded(QPoint pos)
{
    for(int i=0; i<chunk_ptr_list.length(); i++){
        if(chunk_ptr_list[i]->getPosition() == pos)
            return true;
    }
    return false;
}

UnitSpace * World::loadUnitSpace(UnitSpace * space, QVector3D c, QString type)
{
    if(type == "terrain"){
        space = new Terrain(c);
        QQmlComponent component2(m_appEngine,QUrl("qrc:/terrain.qml"));
        QQuickItem * obj2 = qobject_cast<QQuickItem*>(component2.create());
        obj2->setParentItem(root);
        obj2->setParent(m_appEngine);
        space->assignObj(obj2);
        space->updateDisplay();
        //qDebug()<<c<<space->position();
        //qDebug()<<space->position()<<space->getObj()->position()<<space->getObj()->height();

    }
    if(type == "air"){
        space = new Air(c);
    }

    return space;
}



void World::resolveCollision(Entity *entity, UnitSpace *space)
{

    if(entity->y() + entity->getHeight() - 1 > space->y() * Constants::tile_width_pixels && entity->y() + 1 < Constants::tile_width_pixels * (space->y() + space->height())){
        float rightBound = Constants::tile_width_pixels * (space->position().x() + space->width());
        if(entity->x() < rightBound && entity->x() > rightBound - abs(entity->getVelocity().x()) - 1){
            entity->setX(Constants::tile_width_pixels * (space->position().x() + space->width()));
        }
        float leftBound = Constants::tile_width_pixels * space->position().x();
        if(entity->x() + entity->getWidth() > leftBound && entity->x() + entity->getWidth() < leftBound + abs(entity->getVelocity().x()) + 1){
            entity->setX(Constants::tile_width_pixels * (space->position().x()) - entity->getWidth());
        }
    }
    if(entity->x() + entity->getWidth() - 1 > space->x() * Constants::tile_width_pixels && entity->x() + 1 < Constants::tile_width_pixels * (space->x() + space->width())){
        float botBound = Constants::tile_width_pixels * (space->position().y() + space->height());
        if(entity->y() < botBound && entity->y() > botBound - abs(entity->getVelocity().y()) - 1){
            entity->setY(Constants::tile_width_pixels * (space->position().y() + space->height()));
        }
        float topBound = Constants::tile_width_pixels * space->position().y();
        if(entity->y() + entity->getHeight() > topBound && entity->y() + entity->getHeight() < topBound + abs(entity->getVelocity().y()) + 1){
            entity->setY(Constants::tile_width_pixels * (space->position().y()) - entity->getHeight());
        }
    }

}

