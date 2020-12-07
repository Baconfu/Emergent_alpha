#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

#include <QQmlApplicationEngine>
#include <QQuickItem>


#include <world.h>
#include <entity.h>


class DebugOverlay
{
public:
    DebugOverlay(QQuickItem * obj = nullptr, World * worldptr = nullptr,QQmlApplicationEngine * appEngine = nullptr);

    void showEntityInfo(Entity * e);

    QString vectorToString(QVector3D v){
        return QString::number(v.x()) + "," + QString::number(v.y()) + "," + QString::number(v.z());
    }
    QString vectorToString(QVector2D v){
        return QString::number(v.x()) + "," + QString::number(v.y());
    }
    QString vectorToString(QPoint v){
        return QString::number(v.x()) + "," + QString::number(v.y());
    }

private:
    int mode = 0;

    QQmlApplicationEngine * m_appEngine = nullptr;

    enum debugMode {
        player = 0,
        entity = 1
    };



    World * m_worldPtr = nullptr;
    QQuickItem * m_obj = nullptr;


    QQuickItem * entityInfo = nullptr;
};

#endif // DEBUGOVERLAY_H
