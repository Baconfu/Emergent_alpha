#include "engine.h"
#include <QDebug>


Engine::Engine(QObject *parent, QQmlApplicationEngine *engine, QQuickWindow *window):
    QObject(parent)
{
    m_appEngine = engine;
    m_window = window;

    root = window->findChild<QQuickItem*>("root");

    connect(window,SIGNAL(keyPressed(int)),this,SLOT(keyPressed(int)));
    connect(window,SIGNAL(keyReleased(int)),this,SLOT(keyReleased(int)));





    //DEV
    //generateWorld();
    //DEV

    //DEV: no world loading

    loadWorld();
    tester = new TestAssistant(world);

    timer = new QTimer;
    timer->setInterval(18);

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));



    timer->start();

}


void Engine::loadWorld()
{
    world = new World(m_appEngine, m_window, QPoint(0,0));
}

void Engine::generateWorld()
{
    worldGen = new WorldGenerator();
}


void Engine::keyPressed(int event_key)
{
    //qDebug()<<"Pressed:"<<event_key;
    newPressedKey(event_key);

    world->keyPressed(event_key);
}

void Engine::keyReleased(int event_key)
{
    //qDebug()<<"Released:"<<event_key;
    removePressedKey(event_key);

    world->keyRelease(event_key);
}

void Engine::mouseMoved(int x, int y)
{
    mousePos = QPointF(x,y);
    qDebug()<<mousePos;
}

void Engine::mousePressed()
{

}


void Engine::timeout()
{
    //Drives game loop




    //DEV: no world

    world->iterate();


}
