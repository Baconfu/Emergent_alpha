#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>

class Engine: public QObject
{
    Q_OBJECT
public:
    Engine(QObject * parent,QQmlApplicationEngine * engine,QQuickWindow * window);



private:
    QQuickWindow * m_window = nullptr;
    QQmlApplicationEngine * m_appEngine = nullptr;
    QQuickItem * root = nullptr;



public slots:
    void keyPressed(int event_key);

};

#endif // ENGINE_H
