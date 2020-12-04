#ifndef RIDGE_H
#define RIDGE_H

#include <QPointF>
#include <QRandomGenerator>
#include <QVector>
#include <QVector2D>

#include <hex.h>

class Ridge
{
public:
    Ridge(Hex * origin, Hex * destination, QRandomGenerator * gen);

    void createPath();
    QVector<QPointF> getPath(){return path;}

    Hex * getOrigin(){return m_origin;}
    Hex * getDestination(){return m_destination;}

private:
    QRandomGenerator * gen = nullptr;

    Hex * m_origin =  nullptr;
    Hex * m_destination = nullptr;

    QVector2D rotateVector(QVector2D vector,float angle);
    float getVectorAngle(QVector2D vector);

    QVector<QPointF> path;
};

#endif // RIDGE_H
