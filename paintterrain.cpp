#include "paintterrain.h"

#include <math.h>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QSGRectangleNode>


PaintTerrain::PaintTerrain(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(ItemHasContents,true);
}

PaintTerrain::~PaintTerrain()
{

}


QSGNode *PaintTerrain::updatePaintNode(QSGNode * oldNode, QQuickItem::UpdatePaintNodeData *)
{
    if(!oldNode){
        QSGGeometryNode *topNode = nullptr;

        QSGGeometry * topGeometry = nullptr;
        topNode = new QSGGeometryNode;
        topGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);
        topGeometry->setDrawingMode(GL_POLYGON);
        topGeometry->vertexDataAsPoint2D()[0].set(0,0);
        topGeometry->vertexDataAsPoint2D()[1].set(0,Constants::tile_width_pixels*sin(1.047));
        topGeometry->vertexDataAsPoint2D()[2].set(Constants::tile_width_pixels,Constants::tile_width_pixels*sin(1.047));
        topGeometry->vertexDataAsPoint2D()[3].set(width(),0);



        topNode->setGeometry(topGeometry);
        topNode->setFlag(QSGNode::OwnsGeometry);

        QStringList s = QString::number(z()).split(".");

        int level = 0;
        if(s.length() > 1){
            level = s[1].toInt();
        }


        QSGFlatColorMaterial *topMaterial = new QSGFlatColorMaterial;
        QColor topColor = QColor::fromRgb(160 + level*20 , 160 + level*20 , 160 + level*20);
        topMaterial->setColor(topColor);

        topNode->setMaterial(topMaterial);
        topNode->setFlag(QSGNode::OwnsMaterial);

        m_topNode = topNode;


        QSGGeometry * sideGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);
        sideGeometry->setDrawingMode(GL_POLYGON);
        sideGeometry->vertexDataAsPoint2D()[0].set(0,Constants::tile_width_pixels*sin(1.047));
        sideGeometry->vertexDataAsPoint2D()[1].set(0,height());
        sideGeometry->vertexDataAsPoint2D()[2].set(width(),height());
        sideGeometry->vertexDataAsPoint2D()[3].set(width(),Constants::tile_width_pixels*sin(1.047));


        QSGFlatColorMaterial *sideMaterial = new QSGFlatColorMaterial;
        QColor sideColor = QColor::fromRgb(70 + level*40, 70 + level*40 , 70 + level*40);
        sideMaterial->setColor(sideColor);

        QSGGeometryNode * sideNode  = new QSGGeometryNode;
        sideNode->setGeometry(sideGeometry);
        sideNode->setMaterial(sideMaterial);

        sideNode->setFlags(QSGNode::OwnsGeometry|QSGNode::OwnsMaterial);
        topNode->appendChildNode(sideNode);

        m_sideNode = sideNode;

        return topNode;

    } else{
        QSGFlatColorMaterial * topMaterial = new QSGFlatColorMaterial;
        QSGFlatColorMaterial * sideMaterial = new QSGFlatColorMaterial;

        QStringList s = QString::number(z()).split(".");

        int level = 0;
        if(s.length() > 1){
            level = s[1].toInt();
        }

        QColor topColor = QColor::fromRgb(160 + level*30 , 160 + level*30 , 160 + level*30);
        topMaterial->setColor(topColor);

        QColor sideColor = QColor::fromRgb(70 + level*40, 70 + level*40 , 70 + level*40);
        sideMaterial->setColor(sideColor);

        m_topNode->setMaterial(topMaterial);
        m_sideNode->setMaterial(sideMaterial);


        m_topNode->markDirty(QSGNode::DirtyGeometry);
        m_sideNode->markDirty(QSGNode::DirtyGeometry);

        return m_topNode;
    }

}

/*
void PaintTerrain::paint(QPainter *painter)
{

    QPen pen;
    pen.setWidth(2);
    QBrush brush;
    brush.setColor("grey");


    painter->setPen(pen);
    painter->setBrush(brush);

    QStringList s = QString::number(z()).split(".");

    int level = 0;
    if(s.length() > 1){
        level = s[1].toInt();
    }

    //painter->drawRect(QRect(0,30*sin(1.047),30,height()-30*sin(1.047)));

    painter->fillRect(QRect(0,Constants::tile_width_pixels*sin(1.047),Constants::tile_width_pixels,height()-Constants::tile_width_pixels*sin(1.047)),QColor::fromRgb(70 + level*40, 70 + level*40 , 70 + level*40));

    painter->fillRect(QRect(0,0,width(),Constants::tile_width_pixels*sin(1.047)),QColor::fromRgb(160 + level*30 , 160 + level*30 , 160 + level*30));

}*/
