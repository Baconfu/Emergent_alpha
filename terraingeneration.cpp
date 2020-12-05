#include "terraingeneration.h"

#include <math.h>

#include <worldgenerator.h>
#include <ridge.h>
#include <tectonicplate.h>

TerrainGeneration::TerrainGeneration(QQuickItem * parent):
    QQuickPaintedItem(parent)
{
    gen = new QRandomGenerator(testSeed);
}

void TerrainGeneration::paint(QPainter *painter)
{
    delete(gen);
    gen = new QRandomGenerator(testSeed);
    map = new QImage(size().toSize(),QImage::Format::Format_RGB32);

    map->fill(QColor(120,120,120));

    QImage * outline = new QImage(600,600,QImage::Format_ARGB32);

    QPainter paintOutline(outline);

    WorldGenerator * generator = new WorldGenerator(gen);
    QVector<QPoint> plates;
    for(int i=-2; i<3; i++){
        for(int j=-2; j<3; j++){
            plates.append(QPoint(i,j));
        }
    }
    for(int i=0; i<plates.length(); i++){
        generator->generatePlate(plates[i]);
    }

    QVector<Ridge*> allRidges = generator->getAllRidges();
    QVector<Hex*> allHexes = generator->getAllHexes();

    for(int i=0; i<allRidges.length(); i++){
        QVector<QPointF> ridge = allRidges[i]->getPath();
        for(int j=0; j<ridge.length()-1; j++){

            paintOutline.drawLine((ridge[j]/10)+QPointF(300,300),(ridge[j+1]/10)+QPointF(300,300));
        }
    }



    QRect frame(0,0,width(),height());

    //painter->drawImage(frame,*outline);



    QVector<TectonicPlate*> allPlates = generator->getAllPlates();

    //qDebug()<<allPlates[13]->getPath();


    for(int i=0; i<allPlates.length(); i++){
        int gray = gen->generate()%10 + 124;
        painter->setBrush(QColor(gray,gray,gray));
        painter->setPen(Qt::NoPen);
        painter->drawPath(allPlates[i]->getPath());
    }



    //painter->drawPath(allPlates[12]->getPath());
    delete(generator);

    testSeed+=1;
    delete(map);
}


QVector2D TerrainGeneration::rotateVector(QVector2D vector, float angle)
{
    return QVector2D(float(vector.length())*cos(getVectorAngle(vector)+angle),
                     float(vector.length())*sin(getVectorAngle(vector)+angle));
}

float TerrainGeneration::getVectorAngle(QVector2D vector)
{
    float angle = atan(vector.y()/vector.x());
    if(vector.x()<0){
        angle += 3.1415926;
    }else{
        if(vector.y()<0){
            angle += 2*3.1415926;
        }
    }
    return angle;
}

void TerrainGeneration::refresh()
{

}


