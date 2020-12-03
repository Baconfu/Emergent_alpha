#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QTimer>

#include <testassistant.h>
#include <world.h>
#include <worldgenerator.h>


class Engine: public QObject
{
    Q_OBJECT
public:
    Engine(QObject * parent,QQmlApplicationEngine * engine,QQuickWindow * window);



private:
    QQuickWindow * m_window = nullptr;
    QQmlApplicationEngine * m_appEngine = nullptr;
    QQuickItem * root = nullptr;

    QTimer * timer = nullptr;

    TestAssistant * tester = nullptr;

    QVector<int> pressed_keys;
    void newPressedKey(int key_event){if(!pressed_keys.contains(key_event)){pressed_keys.append(key_event);}}
    void removePressedKey(int key_event){pressed_keys.removeOne(key_event);}


    void loadWorld();
    World * world = nullptr;


    void generateWorld();
    WorldGenerator * worldGen = nullptr;

public slots:
    void keyPressed(int event_key);
    void keyReleased(int event_key);

    void timeout();

};


#endif // ENGINE_H
