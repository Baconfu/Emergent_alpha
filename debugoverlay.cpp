#include "debugoverlay.h"

DebugOverlay::DebugOverlay(QQuickItem * obj,World * worldptr,QQmlApplicationEngine * appEngine)
{
    m_obj = obj;
    m_worldPtr = worldptr;
    m_appEngine = appEngine;

    QQmlComponent component(m_appEngine,QUrl("qrc:/entityInfo.qml"));
    QQuickItem * object = qobject_cast<QQuickItem*>(component.create());
    object->setParentItem(m_obj);
    //qDebug()<<m_window->findChild<QQuickItem*>("info_panel");
    obj->setParent(m_appEngine);
    entityInfo = object;

}

void DebugOverlay::showEntityInfo(Entity *e)
{
    entityInfo->findChild<QObject*>("type")->setProperty("text","type: " + e->getTypeName());

    entityInfo->findChild<QObject*>("coordinate")->setProperty("text",vectorToString(e->getPosition()));

    QVector3D tilePos = m_worldPtr->getTilePositionFromPixel(e->getPosition());
    entityInfo->findChild<QObject*>("current_tile")->setProperty("text",
                        vectorToString(tilePos));
    entityInfo->findChild<QObject*>("current_chunk")->setProperty("text",
                        vectorToString(m_worldPtr->getChunkPositionFromTilePosition(tilePos)));


    entityInfo->findChild<QObject*>("velocity")->setProperty("text",
                        vectorToString(e->getVelocity()));



}


