#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <QPoint>
#include <QPointF>
#include <QRandomGenerator>
#include <QVector>

#include <constants.h>
#include <math.h>


class TectonicPlate;
class Ridge;
class Hex;

class WorldGenerator
{
public:
    WorldGenerator(QRandomGenerator * generator = nullptr);

    TectonicPlate * generatePlate(QPoint);

    QVector<Ridge*> getAllRidges();
    QVector<Hex*> getAllHexes();
    QVector<TectonicPlate*> getAllPlates(){return world;}

    void evaluatePlateCollision();

private:
    QRandomGenerator * gen = nullptr;
    QVector<TectonicPlate*> world;



    float hex_radius = Constants::hex_radius_units;

    QPointF plateXVector = QPointF(2 * hex_radius * pow(2*(1-cos(2*3.1415926/3)),0.5),0);
    QPointF plateYVector = QPointF(hex_radius * pow(2*(1 - cos(2*3.1415926/3)),0.5),3*hex_radius);




    QVector<TectonicPlate*> getAdjacentPlates(QPoint position);

    TectonicPlate * getPlate(QPoint position);
};

#endif // WORLDGENERATOR_H
