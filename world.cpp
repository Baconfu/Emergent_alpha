#include "world.h"


#include <constants.h>
#include <entity.h>
#include <player.h>
#include <terrain.h>
#include <testassistant.h>
#include <ladder.h>


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
    player = new Player(QVector3D(0,0,0));

    //Creating player avatar graphics
    QQmlComponent component(engine,QUrl("qrc:/playerAvatar.qml"));
    QQuickItem * obj = qobject_cast<QQuickItem*>(component.create());
    //Parenting graphics item to player
    obj->setParentItem(root);
    obj->setParent(engine);
    player->assignObj(obj);

    player->setDimensions(QVector3D(20,20,40));

    player->updateDisplay();

    createLadder(QVector3D (30,60,0),0);

}

void World::createLadder(QVector3D position,int rotation)
{
    double detectionBoxWidthProportion = 0.9;
    double detectionBoxThickness = 4;

    QQmlComponent ladderComponent(m_appEngine,QUrl("qrc:/ladder.qml"));
    QQuickItem * ladderObj = qobject_cast<QQuickItem*>(ladderComponent.create());


    ladderObj->setParentItem(root);
    ladderObj->setParent(m_appEngine);


    Ladder* newLadder = new Ladder(position,rotation);
    newLadder->assignObj(ladderObj);

    //ladderObj->setPosition(QPointF(World::get2DProjection(position)));
    qDebug()<<"Position of ladder sprite:"<<ladderObj->position();
    //ladderObj->setProperty("m_rotation",rotation);
    //ladderObj->setWidth(Constants::tile_width_pixels);

    newLadder->setDimensions(QVector3D(30,30,30));

    newLadder->updateDisplay();


    if (rotation == 0){
        newLadder->createDetectionBoxPosition(QVector3D((position[0]+Constants::tile_width_pixels*(1-detectionBoxWidthProportion)/2),position[1],position[2]));
        newLadder->createDetectionBoxDimension(QVector3D(Constants::tile_width_pixels*detectionBoxWidthProportion, detectionBoxThickness, Constants::tile_width_pixels));
        qDebug()<<"created hitbox at rotation 0";
        qDebug()<<ladderObj->x()<<ladderObj->y()<<ladderObj->width()<<ladderObj->height();
        qDebug()<<newLadder->position();

    }
    else if (rotation == 1) {

    }
    else if (rotation == 2) {
        newLadder->createDetectionBoxPosition(QVector3D((position[0]+Constants::tile_width_pixels*(1-detectionBoxWidthProportion)/2),position[1]+(Constants::tile_width_pixels-detectionBoxThickness),position[2]));
        newLadder->createDetectionBoxDimension(QVector3D(Constants::tile_width_pixels*detectionBoxWidthProportion, detectionBoxThickness, Constants::tile_width_pixels));
    }
    else if (rotation == 3) {

    }

    appendEntity(newLadder);
    //newLadder->updateDisplay();

    qDebug()<<ladderObj<<ladderObj->position()<<","<<ladderObj->property("m_rotation");
}



void World::iterate()
{
    player->iterate();
    updateCamera();

    QVector<QPoint> screen_bounds;
    int screen_x = root->property("x").toInt();
    int screen_y = root->property("y").toInt();
    screen_bounds.append(getChunkFromTile(getTileFromPixel(QVector3D(screen_x,screen_y,0))));
    screen_bounds.append(getChunkFromTile(getTileFromPixel(QVector3D(screen_x + root->width(), screen_y,0))));
    screen_bounds.append(getChunkFromTile(getTileFromPixel(QVector3D(screen_x,screen_y + root->height(),0))));
    screen_bounds.append(getChunkFromTile(getTileFromPixel(QVector3D(screen_x + root->width(),screen_y + root->height(),0))));

    for(int i=0; i<screen_bounds.length(); i++){
        if(!chunkAlreadyLoaded(screen_bounds[i])){
            environment.append(loadChunk(screen_bounds[i]));
        }
    }




    QVector<QVector3D> player_space = tilesOccupied(player);
    for(int i=0; i<player_space.length(); i++){
        Chunk * chunk = getChunk(getChunkFromTile(player_space[i]));
        UnitSpace * space = chunk->getSpace(getTilePositionInChunk(player_space[i]));
        if(space->collision_player()){
            //qDebug()<<space->position();
            resolveCollision(player,space);
        }
    }


}

void World::keyInputs(int event_key)
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

    root->setX(player->position().x()*-1 + root->width()/2);
    root->setY(player->position().y()*-1 + root->height()/2);
}

Chunk *World::generateChunk(QPoint pos)
{
    Chunk * chunk = new Chunk(pos);
    QVector<UnitSpace*> area;
    for(int i=0; i<Constants::chunk_width_tiles * Constants::chunk_width_tiles; i++){
        int y = (i - i%Constants::chunk_width_tiles)/Constants::chunk_width_tiles;
        int x = i%Constants::chunk_width_tiles;
        if(gen.generate()%100>80){

            area.append(new Terrain(QVector3D(x,y,0)));
        }else{
            area.append(new Air(QVector3D(x,y,0)));
        }
    }
    chunk->setChunkData(area);
    return chunk;
}

Chunk *World::getChunk(QPoint chunk_position)
{
    for(int i=0; i<environment.length(); i++){
        if(environment[i]->getPosition() == chunk_position){
            return environment[i];
        }
    }
    return nullptr;
}

QVector3D World::getTileFromPixel(QVector3D global_pixel_position)
{
    return QVector3D(int(global_pixel_position.x() / Constants::tile_width_pixels),
                     int(global_pixel_position.y() / Constants::tile_width_pixels),
                     int(global_pixel_position.z() / Constants::tile_width_pixels));
}

QPoint World::getChunkFromTile(QVector3D pos)
{
    QVector3D out = (pos - getTilePositionInChunk(pos)) / Constants::chunk_width_tiles;
    return QPoint(out.x(),out.y());
}

QVector3D World::getTilePositionInChunk(QVector3D pos)
{
    return QVector3D(int(pos.x()) % Constants::chunk_width_tiles,int(pos.y()) % Constants::chunk_width_tiles,pos.z());
}

Chunk *World::loadChunk(QPoint pos)
{
    Chunk * chunk = new Chunk(pos);

    QVector<UnitSpace*> area = chunk->loadChunkFromFile();
    int w = Constants::chunk_width_tiles;


    for(int i=0; i<area.length(); i++){
        UnitSpace * u = area[i];
        QVector3D pos = QVector3D(chunk->getPosition().x(),chunk->getPosition().y(),0) * Constants::chunk_width_tiles + u->position();
        if(typeid (*u) == typeid (Air)){
            loadUnitSpace(u,pos,"air");
        }else{
            loadUnitSpace(u,pos,"terrain");

            if(gen.generate()%10 > 6){
                loadUnitSpace(u,pos+QVector3D(0,0,1),"terrain");
                if(gen.generate()%10 > 6){
                    loadUnitSpace(u,pos+QVector3D(0,0,2),"terrain");
                }
            }

        }
    }



    return chunk;
}

QVector<QVector3D> World::tilesOccupied(Entity* entity)
{
    QVector<QVector3D> out;
    int width = entity->width();
    int height = entity->height();
    out.append(getTileFromPixel(entity->position()));
    QVector3D tile = getTileFromPixel(entity->position()+QVector3D(width,0,0));
    if(!out.contains(tile)){
        out.append(tile);
    }
    tile = getTileFromPixel(entity->position()+QVector3D(0,height,0));
    if(!out.contains(tile)){
        out.append(tile);
    }
    tile = getTileFromPixel(entity->position()+QVector3D(width,height,0));
    if(!out.contains(tile)){
        out.append(tile);
    }
    //qDebug()<<out<<y+height;
    return out;
}

bool World::chunkAlreadyLoaded(QPoint pos)
{
    for(int i=0; i<environment.length(); i++){
        if(environment[i]->getPosition() == pos)
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

    if(entity->y() + entity->height() - 1 > space->y() * Constants::tile_width_pixels && entity->y() + 1 < Constants::tile_width_pixels * (space->y() + space->height())){
        float rightBound = Constants::tile_width_pixels * (space->position().x() + space->width());
        if(entity->x() < rightBound && entity->x() > rightBound - abs(entity->getVelocity().x()) - 1){
            entity->setX(Constants::tile_width_pixels * (space->position().x() + space->width()));
        }
        float leftBound = Constants::tile_width_pixels * space->position().x();
        if(entity->x() + entity->width() > leftBound && entity->x() + entity->width() < leftBound + abs(entity->getVelocity().x()) + 1){
            entity->setX(Constants::tile_width_pixels * (space->position().x()) - entity->width());
        }
    }
    if(entity->x() + entity->width() - 1 > space->x() * Constants::tile_width_pixels && entity->x() + 1 < Constants::tile_width_pixels * (space->x() + space->width())){
        float botBound = Constants::tile_width_pixels * (space->position().y() + space->height());
        if(entity->y() < botBound && entity->y() > botBound - abs(entity->getVelocity().y()) - 1){
            entity->setY(Constants::tile_width_pixels * (space->position().y() + space->height()));
        }
        float topBound = Constants::tile_width_pixels * space->position().y();
        if(entity->y() + entity->height() > topBound && entity->y() + entity->height() < topBound + abs(entity->getVelocity().y()) + 1){
            entity->setY(Constants::tile_width_pixels * (space->position().y()) - entity->height());
        }
    }

}

