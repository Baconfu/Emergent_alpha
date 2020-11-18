#include "engine.h"

Engine::Engine(QObject *parent, QQmlApplicationEngine *engine, QQuickWindow *window):
    QObject(parent)
{
    m_appEngine = engine;
    m_window = window;

    connect(window,SIGNAL(keyPressed(int)),this,SLOT(keyPressed(int)));
}


void Engine::keyPressed(int event_key)
{
    qDebug()<<event_key;
}
