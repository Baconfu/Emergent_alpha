#ifndef TERRAINGENERATION_H
#define TERRAINGENERATION_H

#include <QImage>
#include <QLine>
#include <QPainter>
#include <QPixmap>
#include <QQuickPaintedItem>
#include <QRandomGenerator>
#include <QVector>

class TerrainGeneration: public QQuickPaintedItem
{
    Q_OBJECT
public:
    TerrainGeneration(QQuickItem * parent = nullptr);

    void paint(QPainter *painter);




private:
    int testSeed = 0;

    QRandomGenerator * gen = nullptr;

    QImage * map = nullptr;

    QVector2D rotateVector(QVector2D vector,float angle);

    float getVectorAngle(QVector2D vector);


public slots:
    void refresh();
};

#endif // TERRAINGENERATION_H
