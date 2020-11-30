#include "terraingeneration.h"

#include <math.h>

TerrainGeneration::TerrainGeneration(QQuickItem * parent):
    QQuickPaintedItem(parent)
{
    gen = new QRandomGenerator(3);
}

void TerrainGeneration::paint(QPainter *painter)
{
    map = new QImage(size().toSize(),QImage::Format::Format_RGB32);

    map->fill(QColor(120,120,120));

    QVector<QPointF> ridge;
    QPointF init = QPoint(gen->generate()%100 + 250,gen->generate()%100 + 250);
    ridge.append(init);
    QVector2D vector = QVector2D((gen->generate()%1000-500) / 1000,(gen->generate()%1000-500) / 1000);
    for(int i=0; i<100; i++){


        int rand = gen->generate()%1000;
        float angle = (rand - 500);

        vector.normalize();
        QVector2D home = QVector2D(ridge[0] - ridge[i]);
        if(!home.isNull()){
            float tendency = getVectorAngle(home) - getVectorAngle(vector);
            //angle+=tendency/10;
            qDebug()<<tendency;

        }

        vector = rotateVector(vector,angle/4000);

        int length = (gen->generate()%10+10)/5;

        ridge.append(ridge[i]+length*vector.toPointF());
    }
    QPen pen;
    pen.setColor(QColor(0,200,0));
    pen.setWidth(1);
    QPainter imagePainter(map);
    painter->setPen(pen);

    imagePainter.setPen(pen);

    for(int i=0; i<ridge.length()-1; i++){

        painter->drawLine(ridge[i],ridge[i+1]);

    }
    qDebug()<<ridge;


    /*


    for(int i=0; i<map->width(); i++){
        for(int j=0; j<map->height(); j++){
            QColor col = QColor(gen->generate()%255,gen->generate()%255,gen->generate()%255);
            map->setPixelColor(i,j,col);
        }
    }

    */


    QRect bounds = QRect(0,0,width(),height());
    //painter->drawImage(bounds,*map);

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


