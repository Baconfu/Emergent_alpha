#include "hex.h"

#include <math.h>

Hex::Hex(QPointF pos, QRandomGenerator * gen)
{
    position = pos;
    float angle = gen->generate64()%int(2 * 3.1415926 * 1000);
    angle /= 1000;

    float dist = gen->generate64() % int(radius * 1000);
    dist /= 1000;

    focalPoint = QPointF(cos(angle) * dist, sin(angle) * dist);
}
