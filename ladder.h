#ifndef LADDER_H
#define LADDER_H

#include <entity.h>


class Ladder: public Entity
{
public:
    Ladder(QVector3D position, int rotation);
    int span() {return m_span;}
    QVector3D createDetectionBoxPosition (QVector3D newPosition) {m_detectionBoxPosition = newPosition;}
    QVector3D createDetectionBoxDimension (QVector3D newDimension) {m_detectionBoxDimension = newDimension;}

private:
    int m_span;
    QVector3D m_detectionBoxPosition = QVector3D (0,0,0);
    QVector3D m_detectionBoxDimension = QVector3D (0,0,0);

};


#endif // LADDER_H
