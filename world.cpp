#include "world.h"

#include <constants.h>
#include <testassistant.h>


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
    player = new Player();
    //set player on root window.
    player->setParentItem(root);

    //Creating player avatar graphics
    QQmlComponent component(engine,QUrl("qrc:/playerAvatar.qml"));
    QQuickItem * obj = qobject_cast<QQuickItem*>(component.create());
    //Parenting graphics item to player
    obj->setParentItem(player);
    obj->setParent(engine);
    player->assignObj(obj);

    player->setPosition(QPointF(100,100));



}

void World::iterate()
{
    player->iterate();

    QPoint current_chunk = getCurrentChunk(player->currentTile());
    if(!chunkAlreadyLoaded(current_chunk)){
        environment.append(loadChunk(current_chunk));
        TestAssistant * tester = new TestAssistant(this);
        tester->testChunks();
        delete(tester);

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

int World::index(int i, int j)
{
    return j*Constants::chunk_width_tiles*Constants::world_width_chunks + i;

}

Chunk *World::generateChunk(QPoint pos)
{
    Chunk * chunk = new Chunk(pos);
    QVector<UnitSpace*> area;
    for(int i=0; i<Constants::chunk_width_tiles * Constants::chunk_width_tiles; i++){
        if(gen.generate()%100>80){
            area.append(new Terrain());
        }else{
            area.append(new Air());
        }
    }
    chunk->setChunkData(area);
    return chunk;
}

QPoint World::getCurrentChunk(QPoint pos)
{
    return (pos - getPositionInChunk(pos)) / Constants::chunk_width_tiles;
}

QPoint World::getPositionInChunk(QPoint pos)
{
    return QPoint(int(pos.x()) % Constants::chunk_width_tiles,int(pos.y()) % Constants::chunk_width_tiles);
}

Chunk *World::loadChunk(QPoint pos)
{
    Chunk * chunk = new Chunk(pos);

    QVector<UnitSpace*> area = chunk->loadChunkFromFile();
    int w = Constants::chunk_width_tiles;


    for(int i=0; i<area.length(); i++){
        UnitSpace * u = area[i];
        QPoint pos = chunk->getPosition() * Constants::chunk_width_tiles + QPoint(i%w,i/w);
        if(typeid (*u) == typeid (Air)){
            loadUnitSpace(Coordinate(pos.x(),pos.y(),0),"air");
        }else{
            loadUnitSpace(Coordinate(pos.x(),pos.y(),0),"terrain");
        }
    }



    return chunk;
}

bool World::chunkAlreadyLoaded(QPoint pos)
{
    for(int i=0; i<environment.length(); i++){
        if(environment[i]->getPosition() == pos)
            return true;
    }
    return false;
}

UnitSpace * World::loadUnitSpace(Coordinate c, QString type)
{
    UnitSpace * space = nullptr;
    if(type == "terrain"){
        space = new Terrain();
        QQmlComponent component2(m_appEngine,QUrl("qrc:/terrain.qml"));
        QQuickItem * obj2 = qobject_cast<QQuickItem*>(component2.create());
        obj2->setParentItem(root);
        obj2->setParent(m_appEngine);
        space->assignObj(obj2);

        space->setPosition(c);
    }
    if(type == "air"){
        space = new Air();
    }


    return space;
}

