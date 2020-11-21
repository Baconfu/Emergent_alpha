#include "world.h"

#include <constants.h>
#include <testassistant.h>

World::World(QQmlApplicationEngine * engine, QQuickWindow * window, QPoint coordinates)
{


    //Pointers allows <World> to create and draw componenets.
    m_appEngine = engine;
    m_window = window;

    //Root: the root item in the window. Base frame
    root = window->findChild<QQuickItem*>("root");

    //load world from coordinates
    loadUnitSpace(Coordinate(3,2,0));
    loadUnitSpace(Coordinate(3,3,0));


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

UnitSpace * World::loadUnitSpace(Coordinate c)
{
    Terrain * space = new Terrain(c);

    return space;
}

