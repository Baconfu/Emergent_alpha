#ifndef TERRAINGENERATION_H
#define TERRAINGENERATION_H

#include <QLine>
#include <QPainter>
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
    QRandomGenerator * gen = nullptr;

    QVector<float> map;



public slots:
    void refresh();
};

#endif // TERRAINGENERATION_H
