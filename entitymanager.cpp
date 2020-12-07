#include "entitymanager.h"
#include "paintladder.h"

EntityManager::EntityManager(World * worldptr)
{
    m_worldptr = worldptr;
}

Entity* EntityManager::differentiate(QVector3D position, QVector3D dimension, int type, int rotation)
{


    if (type == ladder) {
        //qDebug()<<"rotation value in differentiate function"<<rotation;
        return differentiateToLadder(position, dimension, rotation);

        //IDString = "ladder";
    }

    if (type == player) {
        return differentiateToPlayer(position);
    }

    else{return nullptr;}

    /*QQmlComponent ladderComponent(m_appEngine,QUrl("qrc:/"+IDString+".qml"));
    QQuickItem * entityObjPtr = qobject_cast<QQuickItem*>(ladderComponent.create());

    entityObjPtr->setParentItem(m_appEngine->rootObjects()[0]->findChild<QQuickItem*>("root"));
    entityObjPtr->setParent(m_appEngine);
    differentiatedEntity->assignObj(entityObjPtr);
    */
}

Entity* EntityManager::differentiateToLadder(QVector3D position, QVector3D dimension, int rotation){

    Ladder* newLadder = new Ladder(m_worldptr,position,rotation);

    newLadder->setRotation(rotation);
    newLadder->setDimension(dimension);

    double detectionBoxWidthProportion = 0.9;
    double detectionBoxHeightProportion = 0.1;

    qDebug()<<"ladder rotation in differentiateToLadder"<<newLadder->getRotation();

    if (rotation == 0){

        qDebug()<<"ladder detection box 0 created";
        newLadder->setDetectionBoxPosition(QVector3D(
                                               (position[0]+Constants::tile_width_pixels*(1-detectionBoxWidthProportion)/2),
                                                position[1],
                                                position[2]));
        newLadder->setDetectionBoxDimension(QVector3D(
                                                Constants::tile_width_pixels*detectionBoxWidthProportion,
                                                Constants::tile_width_pixels*detectionBoxHeightProportion,
                                                Constants::tile_width_pixels));

    }
    else if (rotation == 1) {

    }
    else if (rotation == 2) {
        qDebug()<<"ladder detection box 2 created";
        newLadder->setDetectionBoxPosition(QVector3D((
                                                position[0]+(Constants::tile_width_pixels*(1-detectionBoxWidthProportion)/2)),
                                                position[1]+(Constants::tile_width_pixels-Constants::tile_width_pixels*detectionBoxHeightProportion),
                                                position[2]));
        newLadder->setDetectionBoxDimension(QVector3D(
                                                Constants::tile_width_pixels*detectionBoxWidthProportion,
                                                Constants::tile_width_pixels*detectionBoxHeightProportion,
                                                Constants::tile_width_pixels));
    }
    else if (rotation == 3) {

    }

    return newLadder->getEntityPtr();
}

Entity *EntityManager::differentiateToPlayer(QVector3D position)
{
    QVector3D initialPlayerPosition = QVector3D(0,0,30);
    QVector3D initialPlayerDimension = QVector3D(Constants::player_width_pixels,Constants::player_width_pixels,Constants::player_height_pixels);
    Player* player = new Player(position,nullptr,m_worldptr);


    player->setDimension(initialPlayerDimension);
    player->setDetectionBoxPosition(initialPlayerPosition);
    player->setDetectionBoxDimension(initialPlayerDimension);

    //qDebug()<<player->getDetectionBoxPosition()<<player->getDetectionBoxDimensionGlobalPosition();

    player->setCurrentTile(m_worldptr->getTilePtrListFromPixel(initialPlayerPosition));
    return player->getEntityPtr();
}
