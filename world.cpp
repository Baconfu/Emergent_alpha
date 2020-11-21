#include "world.h"

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
}

void World::keyInputs(int event_key)
{
    player->move(event_key);
}

void World::keyRelease(int event_key)
{
    player->stop(event_key);
}

UnitSpace * World::loadUnitSpace(Coordinate c)
{
    Terrain * space = new Terrain(c);
    environment.append(space);
    QQmlComponent component2(m_appEngine,QUrl("qrc:/terrain.qml"));
    QQuickItem * obj2 = qobject_cast<QQuickItem*>(component2.create());
    obj2->setParentItem(root);
    obj2->setParent(m_appEngine);
    space->assignObj(obj2);
    return space;
}

