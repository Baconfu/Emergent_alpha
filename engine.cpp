#include "engine.h"
#include <QDebug>


#include <QElapsedTimer>

Engine::Engine(QObject *parent, QQmlApplicationEngine *engine, QQuickWindow *window):
    QObject(parent)
{
    m_appEngine = QSharedPointer<QQmlApplicationEngine>(engine);
    m_window = QSharedPointer<QQuickWindow> (window);

    root = QSharedPointer<QQuickItem>(window->findChild<QQuickItem*>("root"));

    connect(window,SIGNAL(keyPressed(int)),this,SLOT(keyPressed(int)));
    connect(window,SIGNAL(keyReleased(int)),this,SLOT(keyReleased(int)));
    connect(window,SIGNAL(closingWindow()),this,SLOT(closingWindow()));

    loadWorld();

    timer = QSharedPointer<QTimer>(new QTimer);
    timer->setInterval(18);

    connect(timer.data(),SIGNAL(timeout()),this,SLOT(timeout()));

    tester = new TestAssistant(world);

    timer->start();
}

Engine::~Engine()
{
    delete(tester);
    delete(world);
}

void Engine::loadWorld()
{
    world = new World(m_appEngine.data(), m_window.data(), QPoint(0,0));
}


void Engine::keyPressed(int event_key)
{
    ////qDebug()<<"Pressed:"<<event_key;
    newPressedKey(event_key);

    world->keyPressed(event_key);
}

void Engine::keyReleased(int event_key)
{
    ////qDebug()<<"Released:"<<event_key;
    removePressedKey(event_key);

    world->keyRelease(event_key);
}

void Engine::closingWindow()
{

}

void Engine::timeout()
{
    //Drives game loop

    world->iterate();


}
