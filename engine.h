#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QPointer>
#include <QSharedPointer>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QTimer>

#include <testassistant.h>
#include <world.h>


class Engine: public QObject
{
    Q_OBJECT
public:
    Engine(QObject * parent,QQmlApplicationEngine * engine,QQuickWindow * window);
    ~Engine();




private:
    QSharedPointer<QQuickWindow> m_window = nullptr;
    QSharedPointer<QQmlApplicationEngine> m_appEngine = nullptr;
    QSharedPointer<QQuickItem> root = nullptr;

    QSharedPointer<QTimer> timer = nullptr;

    TestAssistant * tester = nullptr;

    QVector<int> pressed_keys;
    void newPressedKey(int key_event){if(!pressed_keys.contains(key_event)){pressed_keys.append(key_event);}}
    void removePressedKey(int key_event){pressed_keys.removeOne(key_event);}


    void loadWorld();
    World * world = nullptr;


public slots:
    void keyPressed(int event_key);
    void keyReleased(int event_key);
    void closingWindow();
    void timeout();

};


#endif // ENGINE_H
