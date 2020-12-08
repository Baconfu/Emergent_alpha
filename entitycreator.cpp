#include "entitycreator.h"
#include "paintladder.h"

EntityCreator::EntityCreator(QQmlApplicationEngine * appEngine)
{
    m_appEngine = appEngine;
}

//Specifications:
/*
 * This class now only creates the entity pointer and specifies its DIMENSIONS. No definition is given to the entity position.
 * The method "createEntity" is called, and generates the QQmlcomponent.
 * The methods "create<entity>" are called by "createEntity" and generate the Entity * pointer with dimensions specific to that entity
 *
 * Overall, this class acts like a factory. It produces the Entity, and is not concerned where the entity might end up. In the future, all non-position related operations in entity creation should be ported here.
 *
*/
Entity* EntityCreator::createEntity(int type)
{

    Entity * out = nullptr;
    QQmlComponent * component = nullptr;

    if (type == ladder) {
        component = new QQmlComponent(m_appEngine,QUrl("qrc:/ladder.qml"));
        out = createLadder();
    }

    if (type == player) {
        component = new QQmlComponent(m_appEngine,QUrl("qrc:/player.qml"));
        out =  createPlayer();
    }

    QQuickItem * obj = qobject_cast<QQuickItem*>(component->create());

    obj->setParentItem(m_appEngine->rootObjects()[0]->findChild<QQuickItem*>("root"));
    obj->setParent(m_appEngine);
    out->assignObj(obj);

    return out;
}

Entity* EntityCreator::createLadder()
{

    Ladder* newLadder = new Ladder();

    double detectionBoxWidthProportion = 0.9;
    double detectionBoxHeightProportion = 0.1;

    //qDebug()<<"ladder rotation in differentiateToLadder"<<newLadder->getRotation();

    newLadder->geometry()->setDimensions(QVector3D(
                                            Constants::tile_width_pixels*detectionBoxWidthProportion,
                                            Constants::tile_width_pixels*detectionBoxHeightProportion,
                                            Constants::tile_width_pixels));
}

Entity *EntityCreator::createPlayer()
{
    QVector3D initialPlayerDimension = QVector3D(Constants::player_width_pixels,Constants::player_width_pixels,Constants::player_height_pixels);
    Player* player = new Player();
    player->geometry()->setDimensions(initialPlayerDimension);

    return player;
}
