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

    //DEV

    /*
    QVector2D origin = QVector2D(100,100);
    QVector2D destination = QVector2D(500,500);
    ridge.append(origin.toPointF());
    QVector2D vector = rotateVector(destination - origin,(gen->generate()%1000-500) / 1000);

    float initialLength = (destination-origin).length();
    float cumulativeLength = 0;
    int i = 0;
    while(true){

        if(i>1000){
            break;
        }

        int rand = gen->generate()%1000;
        float angle = (rand - 500);
        angle = angle / 2000;


        vector.normalize();
        QVector2D dest = QVector2D(destination.toPointF() - ridge[i]);
        if(dest.length()<initialLength/6){
            angle /= ((initialLength/5-dest.length())/10);
        }
        if(dest.length()<10){
            ridge.append(destination.toPointF());
            break;
        }
        if(!dest.isNull()){
            float tendency = getVectorAngle(dest) - getVectorAngle(vector);
            if(tendency>3.1415926){
                tendency -= 3.1415926 * 2;

            }
            if(tendency<-3.1415926){
                tendency+=2 * 3.1415926;
            }


            if(cumulativeLength < initialLength/2){
                tendency/=10;
            }
            angle+=tendency/5;
            //qDebug()<<tendency;

        }

        vector = rotateVector(vector,angle);

        int length = (gen->generate()%10+10)/5;
        length *= initialLength/565;
        cumulativeLength += length;

        ridge.append(ridge[i]+length*vector.toPointF());

        i+=1;
    }*/

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

            painter->drawLine((ridge[j]/10)+QPointF(300,300),(ridge[j+1]/10)+QPointF(300,300));

        }
    }
    /*
    QPointF hexRad = QPointF(Constants::hex_radius_units,Constants::hex_radius_units);
    for(int i=0; i<allHexes.length(); i++){

        painter->drawEllipse(allHexes[i]->getPosition()/10+QPointF(300,300),Constants::hex_radius_units/10,Constants::hex_radius_units/10);

    }
    QVector<TectonicPlate*> allPlates = generator->getAllPlates();
    QPen pen;
    pen.setColor("red");
    painter->setPen(pen);
    for(int i=0; i<allPlates.length(); i++){

        painter->drawEllipse(allPlates[i]->getPosition()/10 + QPointF(300,300),10,10);
    }*/

    /*
    QPen pen;
    pen.setColor(QColor(0,200,0));
    pen.setWidth(1);
    QPainter imagePainter(map);
    painter->setPen(pen);

    imagePainter.setPen(pen);


    //qDebug()<<ridge;





    for(int i=0; i<map->width(); i++){
        for(int j=0; j<map->height(); j++){
            QColor col = QColor(gen->generate()%255,gen->generate()%255,gen->generate()%255);
            map->setPixelColor(i,j,col);
        }
    }




    QRect bounds = QRect(0,0,width(),height());
    //painter->drawImage(bounds,*map);
    */

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


