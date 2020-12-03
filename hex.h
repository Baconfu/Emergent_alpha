#ifndef HEX_H
#define HEX_H


#include <QPointF>
#include <QRandomGenerator>

#include <constants.h>

class Hex
{
public:
    Hex(QPointF position, QRandomGenerator * gen);

    QPointF getFocalPoint(){return focalPoint+position;}

    QPointF getPosition(){return position;}
    void setPosition(QPointF pos){position = pos;}


private:
    QPointF position;

    float radius = Constants::hex_radius_units;

    QPointF focalPoint;
};

#endif // HEX_H
