#ifndef PAINTTERRAIN_H
#define PAINTTERRAIN_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QSizeF>

#include <constants.h>

class PaintTerrain: public QQuickItem
{
    Q_OBJECT
public:
    PaintTerrain(QQuickItem * parent = nullptr);
    ~PaintTerrain();

    QSGNode * updatePaintNode(QSGNode *, UpdatePaintNodeData *);


private:
    QSGGeometryNode * m_topNode = nullptr;
    QSGGeometryNode * m_sideNode = nullptr;



};

#endif // PAINTTERRAIN_H
