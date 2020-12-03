#ifndef TECTONICPLATE_H
#define TECTONICPLATE_H

#include <math.h>
#include <QPoint>
#include <QPointF>
#include <QRandomGenerator>
#include <QVector>

#include <constants.h>



class Hex;
class Ridge;

class TectonicPlate
{
public:
    TectonicPlate(QPointF position,QPoint hexPosition,QRandomGenerator * generator);

    QPoint getHexPosition(){return hexPosition;}
    QPointF getPosition(){return position;}

    void setNeighbours(QVector<TectonicPlate*>);
    void setNeighbour(int index, TectonicPlate * plate);

    Ridge * getRidge(int index);
    void populateRidges();

    Hex * getHex(int index);
    void populateHexes();




private:
    QRandomGenerator * gen = nullptr;
    float hex_radius = Constants::hex_radius_units;




    QPointF position;
    QPoint hexPosition;



    QVector<TectonicPlate*> neighbours;

    QVector<Ridge*> edges;

    QVector<Hex*> border;
    Hex * center = nullptr;



};

#endif // TECTONICPLATE_H
