#include "worldgenerator.h"

#include <tectonicplate.h>
#include <ridge.h>
#include <hex.h>

WorldGenerator::WorldGenerator(QRandomGenerator * generator)
{

    gen = generator;

}

TectonicPlate *WorldGenerator::generatePlate(QPoint hexPosition)
{
    QPointF position = hexPosition.x() * plateXVector + hexPosition.y() * plateYVector;
    TectonicPlate * plate = new TectonicPlate(position,hexPosition,gen);

    plate->setNeighbours(getAdjacentPlates(hexPosition));
    plate->populateHexes();
    plate->populateRidges();
    world.append(plate);
    return plate;

}

QVector<Ridge *> WorldGenerator::getAllRidges()
{
    QVector<Ridge*> out;
    for(int i=0; i<world.length(); i++){
        for(int j=0; j<6; j++){
            Ridge * ridge = world[i]->getRidge(j);
            if(!out.contains(ridge)){
                out.append(ridge);
            }
        }

    }
    return out;
}

QVector<Hex *> WorldGenerator::getAllHexes()
{
    QVector<Hex*> out;
    for(int i=0; i<world.length(); i++){
        for(int j=0; j<6; j++){
            Hex * hex = world[i]->getHex(j);
            if(!out.contains(hex)){
                out.append(hex);
            }
        }
    }
    return out;
}

void WorldGenerator::evaluatePlateCollision()
{

}

QVector<TectonicPlate *> WorldGenerator::getAdjacentPlates(QPoint position)
{
    QVector<TectonicPlate*> out;
    out.append(getPlate(position + QPoint(1,0)));
    out.append(getPlate(position + QPoint(0,1)));
    out.append(getPlate(position + QPoint(-1,1)));
    out.append(getPlate(position + QPoint(-1,0)));
    out.append(getPlate(position + QPoint(0,-1)));
    out.append(getPlate(position + QPoint(1,-1)));
    return out;
}

TectonicPlate *WorldGenerator::getPlate(QPoint position)
{
    for(int i=0; i<world.length(); i++){
        if(world[i]->getHexPosition() == position){
            return world[i];
        }
    }
    return nullptr;
}

