#include "entitymanager.h"
#include "paintladder.h"

EntityManager::EntityManager(World * worldptr)
{
    myWorld = worldptr;
}

Entity* EntityManager::differentiate(QVector3D position, QVector3D dimension, int type, int rotation)
{


    if (type == ladder) {
        qDebug()<<"rotation value in differentiate function"<<rotation;
        return differentiateToLadder(position, dimension, rotation);

        //IDString = "ladder";
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

    Ladder* newLadder = new Ladder(myWorld,position,rotation);

    newLadder->setRotation(rotation);
    //PaintLadder.setRotation(rotation);

    double detectionBoxWidthProportion = 0.9;
    double detectionBoxHeightProportion = 0.1;

    qDebug()<<"ladder rotation in differentiateToLadder"<<newLadder->getRotation();

    if (rotation == 0){
        newLadder->setDetectionBoxPosition(QVector3D((position[0]+Constants::tile_width_pixels*(1-detectionBoxWidthProportion)/2),position[1],position[2]));
        newLadder->setDetectionBoxDimension(QVector3D(Constants::tile_width_pixels*detectionBoxWidthProportion, Constants::tile_width_pixels*detectionBoxHeightProportion, Constants::tile_width_pixels));

    }
    else if (rotation == 1) {

    }
    else if (rotation == 2) {
        qDebug()<<"created detection box in rotation 2";
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