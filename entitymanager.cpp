#include "entitymanager.h"
#include "paintladder.h"

EntityManager::EntityManager()
{

}

Entity* EntityManager::differentiate(int type, int rotation)
{

    Entity * out = nullptr;
    QQmlComponent * component = nullptr;

    if (type == ladder) {
        component = new QQmlComponent(m_appEngine,QUrl("qrc:/ladder.qml"));
        out = differentiateToLadder(position, rotation);
    }

    if (type == player) {
        component = new QQmlComponent(m_appEngine,QUrl("qrc:/player.qml"));
        out =  differentiateToPlayer(position);
    }

    QQuickItem * obj = qobject_cast<QQuickItem*>(component->create());

    obj->setParentItem(m_appEngine->rootObjects()[0]->findChild<QQuickItem*>("root"));
    obj->setParent(m_appEngine);
    out->assignObj(obj);

    return out;
}

Entity* EntityManager::differentiateToLadder(QVector3D position, int rotation){

    Ladder* newLadder = new Ladder(rotation);

    newLadder->setRotation(rotation);
    newLadder->setDimension(QVector3D(30,30,30));

    double detectionBoxWidthProportion = 0.9;
    double detectionBoxHeightProportion = 0.1;

    //qDebug()<<"ladder rotation in differentiateToLadder"<<newLadder->getRotation();

    if (rotation == 0){

        //qDebug()<<"ladder detection box 0 created";
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
        //qDebug()<<"ladder detection box 2 created";
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

    return newLadder;
}

Entity *EntityManager::differentiateToPlayer(QVector3D position)
{
    QVector3D initialPlayerPosition = position;
    QVector3D initialPlayerDimension = QVector3D(Constants::player_width_pixels,Constants::player_width_pixels,Constants::player_height_pixels);
    Player* player = new Player(position,nullptr,m_worldptr);


    player->setDimension(initialPlayerDimension);
    player->setDetectionBoxPosition(initialPlayerPosition);
    player->setDetectionBoxDimension(initialPlayerDimension);

    return player->getEntityPtr();
}
