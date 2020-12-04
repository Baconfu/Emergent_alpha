#include "tectonicplate.h"

#include <hex.h>
#include <math.h>
#include <ridge.h>

#include <QDebug>

TectonicPlate::TectonicPlate(QPointF pos, QPoint hexPos, QRandomGenerator * generator)
{
    gen = generator;
    position = pos;
    hexPosition = hexPos;
    for(int i=0; i<6; i++){
        neighbours.append(nullptr);
        edges.append(nullptr);
        border.append(nullptr);
    }
}

void TectonicPlate::setNeighbours(QVector<TectonicPlate *> adjacent)
{
    neighbours = adjacent;
    for(int i=0; i<adjacent.length(); i++){
        if(adjacent[i]){
            adjacent[i]->setNeighbour((i+3)%6,this);
            edges[i] = adjacent[i]->getRidge((i+3)%6);
            border[i] = adjacent[i]->getHex((i+2)%6);
            if(i==0){
                border[5] = adjacent[0]->getHex(3);
            }else{
                border[i-1] = adjacent[i]->getHex((i+3)%6);
            }


        }

    }
}

void TectonicPlate::setNeighbour(int index, TectonicPlate *plate)
{
    neighbours[index] = plate;
}

Ridge *TectonicPlate::getRidge(int index)
{
    return edges[index];
}

void TectonicPlate::populateRidges()
{
    for(int i=0; i<edges.length(); i++){
        if(!edges[i]){
            if(i== 0){
                edges[i] = new Ridge(border[5],border[0],gen);
            }else{
                edges[i] = new Ridge(border[i-1],border[i],gen);
            }
            edges[i]->createPath();

        }
    }
}

Hex *TectonicPlate::getHex(int index)
{
    return border[index];
}

void TectonicPlate::populateHexes()
{
    for(int i=0; i<border.length(); i++){
        if(!border[i]){
            float angle = 3.1415926/6 + i*3.1415926/3;
            //qDebug()<<i<<hex_radius*2<<sin(angle)<<sin(angle)*2*hex_radius;
            border[i] = new Hex(position + QPointF(2*hex_radius * cos(angle), 2*hex_radius * sin(angle)), gen);
        }
    }
}

QPainterPath TectonicPlate::getPath()
{
    QPainterPath out = QPainterPath(edges[0]->getPath()[0]/10 + QPointF(300,300));
    Hex * origin = edges[0]->getOrigin();
    for(int i=0; i<edges.length(); i++){
        Hex * destination = edges[i]->getDestination();
        QPainterPath sub = QPainterPath(edges[i]->getPath()[0]/10 + QPointF(300,300));
        QVector<QPointF> path = edges[i]->getPath();
        for(int j=0; j<path.length(); j++){
            if(i==0 && j==0){
                continue;
            }
            sub.lineTo(path[j]/10 + QPointF(300,300));
        }
        if(origin == destination){
            //qDebug()<<"reverse";
            sub = sub.toReversed();
            origin = edges[i]->getOrigin();
        }else{
            origin = destination;
        }
        out.connectPath(sub);

    }
    out.setFillRule(Qt::FillRule::WindingFill);
    return out;
}
